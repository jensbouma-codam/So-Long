/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hook.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/12 13:53:08 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/06/01 15:18:46 by jbouma        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	hook_controls(void *ptr)
{
	const int		moves[] = {'W', MLX_KEY_UP, 'A', MLX_KEY_LEFT,
		'D', MLX_KEY_RIGHT, 'S', MLX_KEY_DOWN, 0};
	const int		direction[] = {UP, LEFT, RIGHT, DOWN, HOLD};
	int				move;
	bool			is_moving;

	is_moving = false;
	move = 0;
	while (moves[move])
	{
		if (mlx_is_key_down(((t_game *) ptr)->mlx, moves[move]))
		{
			player_hook(ptr, direction[move / 2]);
			is_moving = true;
		}
		move++;
	}
	if (is_moving == false)
		player_hook(ptr, HOLD);
	if (mlx_is_key_down(((t_game *) ptr)->mlx, MLX_KEY_LEFT_SHIFT))
		((t_game *) ptr)->player->jetpack = true;
	else
		((t_game *) ptr)->player->jetpack = false;
}
