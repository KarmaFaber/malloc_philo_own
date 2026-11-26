/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   platform.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: KarmaFaber <github.com/KarmaFaber>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/26 15:36:39 by KarmaFaber        #+#    #+#             */
/*   Updated: 2026/11/26 15:36:42 by KarmaFaber       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLATFORM_H
# define PLATFORM_H

# include <stddef.h>

long	allocator_page_size(void);
void	*allocator_map(size_t size);
int		allocator_unmap(void *address, size_t size);

#endif
