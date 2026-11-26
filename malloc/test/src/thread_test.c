/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: KarmaFaber <github.com/KarmaFaber>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 14:06:42 by KarmaFaber        #+#    #+#             */
/*   Updated: 2026/11/26 10:19:38 by KarmaFaber       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/test.h"

#define THREAD_COUNT 15
#define ALLOCATIONS_PER_THREAD 300

/**
 * @brief Allocates, checks, and frees one test block.
 *
 * @param size Requested allocation size in bytes.
 * @param iteration Current allocation iteration.
 * @param seed Worker-specific value used in the test pattern.
 * @return 0 if the block passes validation, otherwise -1.
 */
static int	run_allocation(size_t size, size_t iteration, size_t seed)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)malloc(size);
	if (!ptr)
		return (-1);
	ptr[0] = (unsigned char)iteration;
	ptr[size - 1] = (unsigned char)(iteration + seed);
	if (ptr[0] != (unsigned char)iteration
		|| ptr[size - 1] != (unsigned char)(iteration + seed))
	{
		free(ptr);
		return (-1);
	}
	free(ptr);
	return (0);
}

/**
 * @brief Runs repeated allocations for one worker thread.
 *
 * @param arg Pointer to the worker's thread arguments.
 * @return NULL when the worker finishes.
 */
static void	*allocation_worker(void *arg)
{
	size_t	seed;
	size_t	i;
	size_t	size;

	seed = ((struct s_thread_args *)arg)->seed;
	i = 0;
	while (i < ALLOCATIONS_PER_THREAD)
	{
		if (seed == 0 && i == ALLOCATIONS_PER_THREAD / 2)
			show_alloc_mem();
		size = 16 + ((i + seed) % 6) * 4096;
		if (run_allocation(size, i, seed) != 0)
		{
			((struct s_thread_args *)arg)->failed = 1;
			break ;
		}
		i++;
	}
	return (NULL);
}

/**
 * @brief Starts the allocator test worker threads.
 *
 * @param threads Array in which created thread handles are stored.
 * @param args Array of arguments passed to the worker threads.
 * @return Number of threads successfully created.
 */
static size_t	start_threads(pthread_t threads[], struct s_thread_args args[])
{
	size_t	created;

	created = 0;
	while (created < THREAD_COUNT)
	{
		args[created].seed = created * 13;
		args[created].failed = 0;
		if (pthread_create(&threads[created], NULL, allocation_worker,
				&args[created]) != 0)
			break ;
		created++;
	}
	return (created);
}

/**
 * @brief Joins workers and checks their allocation results.
 *
 * @param threads Array of worker thread handles.
 * @param args Array containing each worker's result.
 * @param created Number of threads that were created.
 * @return 1 if all workers join and pass, otherwise 0.
 */
static int	join_threads(pthread_t threads[], struct s_thread_args args[],
		size_t created)
{
	size_t	i;
	int		passed;

	passed = 1;
	i = 0;
	while (i < created)
	{
		if (pthread_join(threads[i], NULL) != 0)
			passed = 0;
		else if (args[i].failed)
			passed = 0;
		i++;
	}
	return (passed);
}

/**
 * @brief Tests concurrent allocations and frees across worker threads.
 *
 * @return void
 */
void	thread_test(void)
{
	pthread_t				threads[THREAD_COUNT];
	struct s_thread_args	args[THREAD_COUNT];
	size_t					created;
	int						passed;

	ft_putstr_fd(C_TEST_THREAD "=== THREAD TEST: PARALLEL ALLOC/FREE ==="
		C_RESET "\n", 1);
	created = start_threads(threads, args);
	passed = (created == THREAD_COUNT);
	if (!join_threads(threads, args, created))
		passed = 0;
	test_report_result("parallel allocations and frees", passed);
}
