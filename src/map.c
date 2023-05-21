/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/12 20:16:27 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/21 22:53:03 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_add(t_map *map, char *line, int y)
{
	t_tiles	*t;
	int		x;

	x = 0;
	while (line[x] != '\0' && line[x] != '\n')
	{
		t = (t_tiles *)memmory_alloccate(1, sizeof(*t));
		t->type = line[x];
		t->x = x;
		t->y = y;
		if (!map->tiles)
			map->tiles = t;
		else
		{
			t->prev = map->tiles;
			map->tiles_last->next = t;
			map->tiles_last->next = t;
		}
		map->tiles_last = t;
		x++;
	}
	map->width = x;
	map->height = y + 1;
}

static t_hooks	*to_window(t_game *g, t_tiles *t, mlx_image_t *i)
{
	t_hooks		*node;
	uint32_t	x;
	uint32_t	y;

	x = t->x * i->width;
	y = t->y * i->height;
	node = (t_hooks *)memmory_alloccate(1, sizeof(*g->hooks));
	node->type = t->type;
	node->key = mlx_image_to_window(g->mlx, i, x, y);
	if (t->type == PLAYER)
	{
		x += 1;
		y += 1;
	}
	node->i = i;
	node->top = y;
	node->bottom = y + i->height;
	node->right = x + i->width;
	node->left = x;
	g->start_x = &node->left;
	g->start_y = &node->top;
	if (g->hooks)
		node->next = g->hooks;
	g->hooks = node;
	return (node);
}

static void	map_draw_element(t_game *g, mlx_image_t *i, char type)
{
	t_tiles			*t;

	t = g->map->tiles;
	while (t)
	{
		if (t->type == type && type == COLLECT)
			g->collect++;
		if (t->type == type
			&& (type == COLLECT || type == PLAYER || type == EXIT))
			to_window(g, t, g->textures->mlx_image)->type = EMPTY;
		if ((t->type == type) && type != PLAYER)
			to_window(g, t, i);
		if (t->type == EXIT && type == EXIT_OPEN)
		{
			g->exit_tile = to_window(g, t, i);
			g->exit_tile->i->enabled = false;
		}
		t = t->next;
	}
}

void	map_draw_tiles(t_game *g)
{
	int			i;
	t_image		*t;
	const char	tile_t[] = {'0', '1', 'E', 'O', 'C', 'P', 0};

	i = 0;
	t = g->textures;
	console_log("Drawing map\n");
	g->collect = 0;
	while (tile_t[i])
	{
		map_draw_element(g, t->mlx_image, tile_t[i++]);
		t = t->next;
	}
}

// Check if map is rectangular
// Check if map has all elements
// Check if map has valid elements
// Check if map has valid amount of elements
// Check if map has valid amount of collectibles
// Check if map has valid amount of exits
// Check if map has valid amount of players
// Check if map has valid amount of walls
// Check if map has valid amount of empty spaces
// Check if map has valid amount of enemies
