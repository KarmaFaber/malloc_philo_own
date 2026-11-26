#ifndef PLATFORM_H
# define PLATFORM_H

# include <stddef.h>

long	allocator_page_size(void);
void	*allocator_map(size_t size);
int		allocator_unmap(void *address, size_t size);

#endif
