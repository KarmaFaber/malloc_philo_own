/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_malloc_memory.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: KarmaFaber <github.com/KarmaFaber>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/26 15:39:46 by KarmaFaber        #+#    #+#             */
/*   Updated: 2026/11/26 15:39:48 by KarmaFaber       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "malloc.h"
#include "inc/test.h"

#undef malloc
#undef free

/**
 * @brief Prints a labeled allocator memory snapshot.
 *
 * @param label Text shown above the memory report.
 * @return void
 */
static void	print_memory_checkpoint(char *label)
{
	ft_putstr_fd("\n=== ", 1);
	ft_putstr_fd(label, 1);
	ft_putstr_fd(" ===\n", 1);
	show_alloc_mem_ex();
}

/**
 * @brief Runs Philo and prints allocator state at key checkpoints.
 *
 * @param argc Number of command-line arguments.
 * @param argv Command-line argument strings.
 * @return 0 on success, otherwise 1.
 */
int	main(int argc, char **argv)
{
	t_program	program = {0};

	if (setvbuf(stdout, NULL, _IONBF, 0) != 0)
		return (perror("setvbuf"), 1);
	if (!check_argvs(argc, argv))
		return (1);
	if (!init_program(&program, argv))
		return (1);
	print_memory_checkpoint("after init_program, before philosopher threads");
	if (!init_philo(&program))
		return (1);
	final_print(&program);
	print_memory_checkpoint("after simulation, philosopher threads joined");
	free_all(&program);
	print_memory_checkpoint("after free_all");
	ft_putstr_fd("\n=== Final allocator zone and block chains ===\n", 1);
	debug_dump_state();
	return (0);
}
