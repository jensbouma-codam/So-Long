/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hook.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/12 13:53:08 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/21 18:35:13 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	hook_exit(t_game *game)
{
	console_log("Thanks for playing! Check https:/jensbouma.com if you like \
for my other projects! :)\n");
	mlx_terminate(game->mlx);
	system("leaks so_long");
	exit(EXIT_SUCCESS);
}

void	hook_interface(mlx_key_data_t keydata, t_game *game)
{	
	if ((keydata.key == MLX_KEY_ESCAPE)
		|| (keydata.key == MLX_KEY_C
			&& keydata.modifier == MLX_CONTROL))
		hook_exit(game);
	return ;
}

void	hook_controls(t_game *game)
{
	int			move;
	int			trigger;
	const int	moves[] = {'W', MLX_KEY_UP, 'A', MLX_KEY_LEFT,
		'D', MLX_KEY_RIGHT, 'S', MLX_KEY_DOWN, 0};
	const int	direction[] = {UP, LEFT, RIGHT, DOWN, HOLD};

	trigger = HOLD;
	move = 0;
	while (moves[move])
	{
		if (mlx_is_key_down(game->mlx, moves[move]))
		{
			trigger = direction[move / 2];
			game->player->dir = trigger;
			player_hook(game);
		}
		move++;
	}
	game->player->dir = trigger;
}
