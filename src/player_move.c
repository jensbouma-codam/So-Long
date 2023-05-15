/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player_move.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/12 17:23:15 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/15 12:12:58 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	update_player(void)
{
	g_img->img->instances[0].x = g_player->x;
	g_img->img->instances[0].y = g_player->y;
}

void	player_jump(void)
{
	if (g_player->action == JUMP && g_player->jump_state == STAND)
	{
		g_player->jump_state = JUMP;
		g_player->action = JUMP_ACTIVE;
		g_player->jump_height = 5;
	}
	if (g_player->jump_state == JUMP
		&& g_player->y - 25 > 0 && g_player->jump_height < 250)
	{
		g_player->y -= 25;
		g_player->jump_height += 25;
	}
	else if (g_player->jump_state == JUMP)
	{
		g_player->jump_state = FALL;
		g_player->jump_height = 0;
	}
}

void	player_fall(void)
{
	if (g_player->jump_state == FALL
		&& g_player->y < g_mlx->height - g_img->img->height)
	{
		if (g_player->y + g_img->img->height + 5 < g_mlx->height)
			g_player->y += 5;
		else
		{
			g_player->y = g_mlx->height - g_img->img->height;
			g_player->jump_state = STAND;
		}
	}
}
