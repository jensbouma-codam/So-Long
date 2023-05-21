/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hook.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/12 13:53:08 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/21 15:19:25 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	hook_exit(void *game)
{
	const t_game	*g = (t_game *)game;

	console_log("Thanks for playing! Check https:/jensbouma.com if you like \
for my other projects! :)\n");
	mlx_terminate(g->mlx);
	system("leaks so_long");
	exit(EXIT_SUCCESS);
}

void	hook_interface(mlx_key_data_t keydata, void *game)
{	
	if ((keydata.key == MLX_KEY_ESCAPE)
		|| (keydata.key == MLX_KEY_C
			&& keydata.modifier == MLX_CONTROL))
		hook_exit(game);
	return ;
}

void	hook_controls(void *game)
{
	t_game		*g;
	int			move;
	int			trigger;
	const int	moves[] = {'W', MLX_KEY_UP, 'A', MLX_KEY_LEFT,
		'D', MLX_KEY_RIGHT, 'S', MLX_KEY_DOWN, 0};
	const int	direction[] = {UP, LEFT, RIGHT, DOWN, HOLD};

	g = (t_game *)game;
	trigger = HOLD;
	move = 0;
	while (moves[move])
	{
		if (mlx_is_key_down(g->mlx, moves[move]))
		{
			trigger = direction[move / 2];
			g->player->dir = trigger;
			player_hook(game);
		}
		move++;
	}
	g->player->dir = trigger;
}
