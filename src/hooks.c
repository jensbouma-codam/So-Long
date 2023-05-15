/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/12 13:53:08 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/15 12:13:33 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	key_hook(mlx_key_data_t keydata, void *param)
{	
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(g_mlx);
}

void	action_hook(void *param)
{
	int			move;
	int			trigger;
	const int	moves[] = {'W', MLX_KEY_UP, 'A', MLX_KEY_LEFT,
		'D', MLX_KEY_RIGHT, 'S', MLX_KEY_DOWN, 0};
	const int	direction[] = {
		UP,
		LEFT,
		RIGHT,
		DOWN,
		HOLD
	};

	trigger = HOLD;
	move = 0;
	while (moves[move])
	{
		if (mlx_is_key_down(param, moves[move]))
		{
			trigger = direction[move / 2];
			g_player->direction = trigger;
			player_hook(param);
		}
		move++;
	}
	g_player->direction = trigger;
}

void	player_hook(void *param)
{
	(void)param;
	if (g_player->jump_state == STAND && g_player->direction == UP)
		g_player->action = JUMP;
	else if (g_player->jump_height == 0 && g_player->direction == DOWN)
		g_player->action = DUCK;
	player_jump();
	player_fall();
	if (g_player->direction == LEFT)
	{
		g_player->action = WALK;
		if (g_player->x > 0)
			g_player->x -= 5;
	}
	else if (g_player->direction == RIGHT)
	{
		g_player->action = WALK;
		if (g_player->x + g_img->img->width + 4 < g_mlx->width)
			g_player->x += 5;
	}
	update_player();
}
