#include "../inc/platform.h"

#include <errno.h>

#ifdef _WIN32
# include <windows.h>
#else
# include <sys/mman.h>
# include <unistd.h>
#endif

/**
 * @brief Returns the system memory page size.
 *
 * @return Page size in bytes, or -1 if the query fails.
 */
long	allocator_page_size(void)
{
#ifdef _WIN32
	SYSTEM_INFO	info;

	GetSystemInfo(&info);
	return ((long)info.dwPageSize);
#else
	return (sysconf(_SC_PAGESIZE));
#endif
}

/**
 * @brief Reserves a writable memory region.
 *
 * @param size Number of bytes to reserve.
 * @return Pointer to the region, or NULL if the reservation fails.
 */
void	*allocator_map(size_t size)
{
#ifdef _WIN32
	void	*address;

	address = VirtualAlloc(NULL, size, MEM_COMMIT | MEM_RESERVE,
			PAGE_READWRITE);
	if (address == NULL)
		errno = ENOMEM;
	return (address);
#else
	void	*address;

	address = mmap(NULL, size, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (address == MAP_FAILED)
		return (NULL);
	return (address);
#endif
}

/**
 * @brief Releases a previously reserved memory region.
 *
 * @param address Start address of the region.
 * @param size Size of the region in bytes.
 * @return 0 on success, or -1 if the region cannot be released.
 */
int	allocator_unmap(void *address, size_t size)
{
#ifdef _WIN32
	(void)size;
	if (VirtualFree(address, 0, MEM_RELEASE) == 0)
	{
		errno = EINVAL;
		return (-1);
	}
	return (0);
#else
	return (munmap(address, size));
#endif
}
