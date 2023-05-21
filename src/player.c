/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 20:45:15 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/21 18:36:46 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>

void	player_update(t_game *game)
{
	uint32_t	old_height;
	t_player	*p;

	p = game->player;
	old_height = p->i->height;
	p->t->walk_anim = animate(p->t->walk_anim, p->t->walk);
	p->i->instances[0].enabled = false;
	if (p->state == JUMP_ACTIVE || p->state == JUMP)
		p->i = p->t->jump->mlx_image;
	else if (p->state == FALL)
		p->i = p->t->hurt->mlx_image;
	else if (p->trigger == DUCK)
		p->i = p->t->duck->mlx_image;
	else if (p->trigger == WALK)
		p->i = p->t->walk_anim->mlx_image;
	else
		p->i = p->t->stand->mlx_image;
	p->i->instances[0].enabled = 1;
	p->i->instances[0].x = p->x;
	p->i->instances[0].y = p->y;
	if (old_height != p->i->height)
		p->y += old_height - p->i->height;
	if (p->i->instances[0].y + p->i->height > (uint32_t)game->mlx->height)
		p->i->instances[0].y = (uint32_t)game->mlx->height - p->i->height;
}

static void	player_jump(t_game *g)
{
	t_player	*p;

	p = g->player;
	if (p->trigger == JUMP && p->state == STAND)
	{
		p->state = JUMP;
		p->trigger = JUMP_ACTIVE;
		p->jump_height = 5 * g->scale;
	}
	if (p->state == JUMP
		&& p->y - 3 * g->scale > 0 && p->jump_height < 150 * g->scale)
	{
		p->y -= 3 * g->scale;
		p->jump_height += 6 * g->scale;
	}
	else if (p->state == JUMP)
	{
		p->state = FALL;
		p->jump_height = 0;
	}
}

static void	player_fall(t_game *g)
{
	t_player	*p;

	p = g->player;
	if (p->state == FALL
		&& p->y < g->mlx->height - p->i->height)
	{
		if (p->y + p->i->height + 2 * g->scale < g->mlx->height)
			p->y += 2 * g->scale;
		else
		{
			p->y = (uint32_t)g->mlx->height - p->i->height;
			p->state = STAND;
		}
	}
}

void	player_hook(t_game *game)
{
	t_player		*p;

	p = game->player;
	if (p->state == STAND && p->dir == UP)
		p->trigger = JUMP;
	else if (p->jump_height == 0 && p->dir == DOWN)
		p->trigger = DUCK;
	else
		p->trigger = STAND;
	player_jump(game);
	player_fall(game);
	if (p->dir == LEFT)
	{
		p->trigger = WALK;
		if (p->x > 0)
			p->x -= 1 * game->scale;
	}
	else if (p->dir == RIGHT)
	{
		p->trigger = WALK;
		if (p->x + p->i->width < (uint32_t)game->mlx->width)
			p->x += 1 * game->scale;
	}
	player_update(game);
}
