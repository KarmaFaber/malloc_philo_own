/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: KarmaFaber <github.com/KarmaFaber>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 12:49:04 by KarmaFaber        #+#    #+#             */
/*   Updated: 2026/11/26 10:39:02 by KarmaFaber       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/test.h"

/**
 * @brief Runs the allocator test suite and reports its result.
 *
 * @return 0 if all tests pass, otherwise 1.
 */
int	main(void)
{
	basic_test();
	write(1, "\n\n", 2);
	split_test();
	write(1, "\n\n", 2);
	extreme_test();
	write(1, "\n\n", 2);
	thread_test();
	test_print_summary();
	return (test_failure_count() != 0);
}
