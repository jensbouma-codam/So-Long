/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   level_draw.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 22:09:02 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/24 23:42:07 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_hook	*level_draw_elements(t_game *g, t_tiles *t, mlx_image_t *i)
{
	t_hook		*node;
	uint32_t	x;
	uint32_t	y;

	x = t->x * i->width;
	y = t->y * i->height;
	node = (t_hook *)memmory_alloccate(1, sizeof(*g->hooks));
	node->type = t->type;
	node->key = mlx_image_to_window(g->mlx, i, x, y);
	if (t->type == PLAYER)
	{
		x += 1;
		y += 1;
	}
	node->i = i;
	node->t = y;
	node->b = y + i->height;
	node->r = x + i->width;
	node->l = x;
	g->start_x = &node->l;
	g->start_y = &node->t;
	if (g->hooks)
		node->next = g->hooks;
	g->hooks = node;
	return (node);
}

static void	level_draw_types(t_game *g, mlx_image_t *i, char type)
{
	t_tiles			*t;

	t = g->level->tiles;
	while (t)
	{
		if (t->type == type && type == COLLECT)
			g->collect++;
		if (t->type == type
			&& (type == COLLECT || type == PLAYER || type == EXIT))
			level_draw_elements(g, t, g->level_textures->mlx_i)->type = EMPTY;
		if ((t->type == type) && type != PLAYER)
			level_draw_elements(g, t, i);
		if (t->type == EXIT && type == EXIT_OPEN)
		{
			g->exit = level_draw_elements(g, t, i);
			g->exit->i->enabled = false;
		}
		t = t->next;
	}
}

void	level_draw(t_game *g)
{
	int			i;
	t_image		*t;
	const char	tile_t[] = {'0', '1', 'E', 'O', 'C', 'P', 0};

	i = 0;
	t = g->level_textures;
	g->collect = 0;
	while (tile_t[i])
	{
		level_draw_types(g, t->mlx_i, tile_t[i++]);
		t = t->next;
	}
}
