/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_printers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: KarmaFaber <github.com/KarmaFaber>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/26 10:37:27 by KarmaFaber        #+#    #+#             */
/*   Updated: 2026/11/26 10:38:32 by KarmaFaber       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/test.h"

/**
 * @brief Writes a null-terminated string to standard output.
 *
 * @param s String to write; NULL is ignored.
 * @return void
 */
static void	put_str(const char *s)
{
	size_t	len;

	if (!s)
		return ;
	len = 0;
	while (s[len])
		len++;
	(void)write(1, s, len);
}

/**
 * @brief Gets the display name for a heap group.
 *
 * @param group Heap group to name.
 * @return Group name, or "UNKNOWN" for an unrecognized group.
 */
static const char	*group_name(t_heap_group group)
{
	if (group == TINY)
		return ("TINY");
	if (group == SMALL)
		return ("SMALL");
	if (group == LARGE)
		return ("LARGE");
	return ("UNKNOWN");
}

/**
 * @brief Gets the display color for a heap group.
 *
 * @param group Heap group whose color is requested.
 * @return ANSI color sequence for the group.
 */
static const char	*group_color(t_heap_group group)
{
	if (group == TINY)
		return (C_TINY);
	if (group == SMALL)
		return (C_SMALL);
	if (group == LARGE)
		return (C_LARGE);
	return (C_RESET);
}

/**
 * @brief Checks whether a block offset points forward within its zone.
 *
 * @param zone Zone containing the block chain.
 * @param current_offset Offset of the current block.
 * @param next_offset Offset of the next block.
 * @return 1 if the next offset is valid, otherwise 0.
 */
static int	is_valid_block_offset(t_zone *zone, uint32_t current_offset,
		uint32_t next_offset)
{
	if (next_offset == 0 || next_offset <= current_offset
		|| (size_t)(next_offset - current_offset) < sizeof(t_block))
		return (0);
	if (zone->total_size < sizeof(t_block))
		return (0);
	if ((size_t)next_offset > zone->total_size - sizeof(t_block))
		return (0);
	return (1);
}

/**
 * @brief Prints the linked list of allocator zones.
 *
 * @return void
 */
void	debug_print_zones_chain(void)
{
	t_zone	*curr;
	char	buf[256];
	int		n;

	curr = g_zones;
	if (curr == NULL)
	{
		put_str("[DEBUG] g_zones it's NULL (there are no areas on the list)\n");
		return ;
	}
	put_str("[DEBUG] Zone chain: ");
	while (curr != NULL)
	{
		n = snprintf(buf, sizeof(buf), "[%p:%s%s%s] -> ",
				(void *)curr, group_color(curr->group),
				group_name(curr->group), C_RESET);
		if (n > 0)
			(void)write(1, buf, (size_t)n);
		curr = curr->next;
	}
	put_str("NULL\n");
}

/**
 * @brief Prints allocator zones and each zone's linked block list.
 *
 * @return void
 */
void	debug_dump_state(void)
{
	t_zone		*curr;
	t_block		*block;
	uint32_t	offset;
	int			zone_idx;
	int			block_idx;
	char		buf[512];
	int			n;

	debug_print_zones_chain();
	if (g_zones == NULL)
		return ;
	curr = g_zones;
	zone_idx = 0;
	while (curr != NULL)
	{
		n = snprintf(buf, sizeof(buf),
				"%s--- Zone %d (%p) ---%s\n"
				"  group      : %s%s%s (%d)\n"
				"  total_size : %zu\n"
				"  free_size  : %zu\n"
				"  next       : %p\n",
				C_ZONE, zone_idx, (void *)curr, C_RESET,
				group_color(curr->group), group_name(curr->group),
				C_RESET, curr->group, curr->total_size, curr->free_size,
				(void *)curr->next);
		if (n > 0)
			(void)write(1, buf, (size_t)n);
		if (curr->total_size > sizeof(t_zone) + sizeof(t_block))
		{
			block = (t_block *)((char *)curr + sizeof(t_zone));
			block_idx = 0;
			offset = sizeof(t_zone);
			while (1)
			{
				n = snprintf(buf, sizeof(buf),
						"    %sBlock %d (%p): size=%zu | is_free=%d | "
						"next_offset=%u | prev_offset=%u%s\n",
						block->is_free ? C_FREE : C_USED,
						block_idx, (void *)block, block->size,
						block->is_free, block->next_offset,
						block->prev_offset, C_RESET);
				if (n > 0)
					(void)write(1, buf, (size_t)n);
				if (!is_valid_block_offset(curr, offset,
						block->next_offset))
					break ;
				offset = block->next_offset;
				block = (t_block *)((char *)curr + offset);
				block_idx++;
			}
		}
		curr = curr->next;
		zone_idx++;
	}
}
