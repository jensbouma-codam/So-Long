/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 20:45:15 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/18 04:45:15 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	player_update(t_player *p)
{
	console_log("Player stand image %p", p->stand->mlx_image);
	p->stand->mlx_image->instances[0].x = p->x;
	p->stand->mlx_image->instances[0].y = p->y;
	console_log("player_update");
	console_log("player position: %d, %d", p->x, p->y);
}

void	player_jump(t_player *p)
{
	if (p->action == JUMP && p->jump_state == STAND)
	{
		p->jump_state = JUMP;
		p->action = JUMP_ACTIVE;
		p->jump_height = 5;
	}
	if (p->jump_state == JUMP
		&& p->y - 25 > 0 && p->jump_height < 250)
	{
		p->y -= 25;
		p->jump_height += 25;
	}
	else if (p->jump_state == JUMP)
	{
		p->jump_state = FALL;
		p->jump_height = 0;
	}
}

void	player_fall(t_player *p)
{
	if (p->jump_state == FALL
		&& p->y < g_mlx->height - (int32_t)p->stand->mlx_image->height)
	{
		if (p->y + (int32_t)p->stand->mlx_image->height + 5 < g_mlx->height)
			p->y += 5;
		else
		{
			p->y = g_mlx->height - (int32_t)p->stand->mlx_image->height;
			p->jump_state = STAND;
		}
	}
}
