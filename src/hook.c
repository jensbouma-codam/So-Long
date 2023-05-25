/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hook.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/12 13:53:08 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/26 00:10:07 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	hook_loop(void *ptr)
{
	detect_hook(ptr);
}

void	hook_controls(void *ptr)
{
	int				move;
	int				trigger;
	const int		moves[] = {'W', MLX_KEY_UP, 'A', MLX_KEY_LEFT,
		'D', MLX_KEY_RIGHT, 'S', MLX_KEY_DOWN, 0};
	const int		direction[] = {UP, LEFT, RIGHT, DOWN, HOLD};
	const t_game	*game = ptr;

	trigger = HOLD;
	move = 0;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT_SHIFT))
		game->player->jetpack = true;
	else if (game->player->jetpack == true)
	{
		game->player->jetpack = false;
		game->player->state = FALL;
	}
	while (moves[move])
	{
		if (mlx_is_key_down(game->mlx, moves[move]))
		{
			trigger = direction[move / 2];
			game->player->dir = trigger;
			// player_hook(ptr);
		}
		move++;
	}
	game->player->dir = trigger;
}
