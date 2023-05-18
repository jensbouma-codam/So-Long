/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/12 20:16:27 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/18 23:19:12 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	to_window(char type, mlx_image_t *i, int x, int y)
{
	t_listner	*node;

	node = (t_listner *)memmory_alloccate(1, sizeof(*g_listner));
	node->type = type;
	node->x = x;
	node->y = y;
	node->key = mlx_image_to_window(g_mlx, i, x, y);
	node->i = i;
	if (g_listner)
		node->next = g_listner;
	g_listner = node;
}

static void	map_draw_element(t_game *game,
	mlx_image_t *i,	mlx_image_t *b, char type)
{
	const uint32_t	x = i->width;
	const uint32_t	y = i->height;
	t_tile			*t;

	t = game->map->tile;
	while (t)
	{
		if (t->type == type)
		{
			if (type == COLLECT || type == PLAYER || type == EXIT)
			{
				if (type == COLLECT)
					to_window(EMPTY, b, t->x * x, t->y * y);
				else
					to_window(type, b, t->x * x, t->y * y);
			}
			if (type != PLAYER)
			{
				to_window(type, i, t->x * x, t->y * y);
			}
		}
		t = t->next;
	}
}

void	map_draw(t_game **game)
{
	int			i;
	t_image		*t;
	const char	map_types[] = {'0', '1', 'E', 'O', 'C', 'P', 0};

	t = (*game)->map_texture;
	console_log("Drawing map");
	i = 0;
	while (map_types[i])
	{
		map_draw_element((*game),
			t->mlx_image, (*game)->map_texture->mlx_image, map_types[i]);
		++i;
		t = t->next;
	}
}

void	map_add(t_map *map, char *line, int y)
{
	t_tile	*t;
	int		x;

	x = 0;
	while (line[x] != '\0' && line[x] != '\n')
	{
		t = (t_tile *)memmory_alloccate(1, sizeof(*t));
		t->type = line[x];
		t->x = x;
		t->y = y;
		if (!map->tile)
			map->tile = t;
		else
		{
			t->prev = map->tile;
			map->last_tile->next = t;
			map->last_tile->next = t;
		}
		map->last_tile = t;
		x++;
	}
	map->width = x;
	map->height = y + 1;
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
