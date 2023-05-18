/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 20:45:15 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/18 18:40:29 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	player_init(t_player *p)
{
	mlx_image_to_window(g_mlx, p->t->stand->mlx_image, 1, 1);
	p->t->stand->mlx_image->instances[0].enabled = 1;
	mlx_image_to_window(g_mlx, p->t->duck->mlx_image, 1, 1);
	p->t->duck->mlx_image->instances[0].enabled = 0;
	mlx_image_to_window(g_mlx, p->t->jump->mlx_image, 1, 1);
	p->t->jump->mlx_image->instances[0].enabled = 0;
	mlx_image_to_window(g_mlx, p->t->hurt->mlx_image, 1, 1);
	p->t->hurt->mlx_image->instances[0].enabled = 0;
	p->i = p->t->stand->mlx_image;
	p->t->walk_anim = p->t->walk;
	mlx_image_to_window(g_mlx, p->t->walk->mlx_image, 1, 0);
	p->t->walk_anim->mlx_image->instances[0].enabled = 0;
}

static mlx_image_t	*player_walk_animation(t_player *p)
{
	static int	frame_delay = 0;
	static bool	firstrun = true;

	if (frame_delay == 0)
	{
		frame_delay = 10;
		if (p->t->walk_anim->next)
		{
			p->t->walk_anim = p->t->walk_anim->next;
			if (firstrun)
				mlx_image_to_window(g_mlx, p->t->walk_anim->mlx_image, 0, 0);
				p->t->walk_anim->mlx_image->instances[0].enabled = 0;
		}
		else
		{
			p->t->walk_anim = p->t->walk;
			firstrun = false;
		}
	}
	else
		frame_delay--;
	return (p->t->walk_anim->mlx_image);
}

void	player_update(t_player *p)
{
	uint32_t	old_height;

	old_height = p->i->height;
	p->t->walk_anim->mlx_image = player_walk_animation(p);
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
	if (p->i->instances[0].y + p->i->height > g_mlx->height)
		p->i->instances[0].y = g_mlx->height - p->i->height;
}

void	player_jump(t_player *p)
{
	if (p->trigger == JUMP && p->state == STAND)
	{
		p->state = JUMP;
		p->trigger = JUMP_ACTIVE;
		p->jump_height = 5 * p->scale;
	}
	if (p->state == JUMP
		&& p->y - 10 * p->scale > 0 && p->jump_height < 250 * p->scale)
	{
		p->y -= 10 * p->scale;
		p->jump_height += 10 * p->scale;
	}
	else if (p->state == JUMP)
	{
		p->state = FALL;
		p->jump_height = 0;
	}
}

void	player_fall(t_player *p)
{
	if (p->state == FALL
		&& p->y < g_mlx->height - (int32_t)p->i->height)
	{
		if (p->y + (int32_t)p->i->height + 5 < g_mlx->height)
			p->y += 5 * p->scale;
		else
		{
			p->y = g_mlx->height - (int32_t)p->i->height;
			p->state = STAND;
		}
	}
}
