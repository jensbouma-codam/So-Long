/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   level_check_path.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/25 22:42:41 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/25 22:42:52 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// check if there is a path from the player to the exit
static void	level_fill_neigbours(t_tiles *tiles, uint32_t x, uint32_t y)
{
	t_tiles	*n;

	n = tiles;
	while (n)
	{
		if (((n->x == x - 1 && n->y == y)
				|| (n->x == x + 1 && n->y == y)
				|| (n->x == x && n->y == y - 1)
				|| (n->x == x && n->y == y + 1))
			&& n->type != WALL && n->reachable == false)
		{
			n->reachable = true;
			level_fill_neigbours(tiles, n->x, n->y);
		}
		n = n->next;
	}
}

void	level_check_path(t_level *level)
{
	t_tiles		*t;

	t = level->tile;
	while (t)
	{
		if (t->reachable == true)
			level_fill_neigbours(level->tile, t->x, t->y);
		t = t->next;
	}
	t = level->tile;
	while (t)
	{
		if (t->reachable == false && (t->type != WALL && t->type != EMPTY))
			error("No path to the exit or collectibles");
		t = t->next;
	}
}
