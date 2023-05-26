/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hook.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/12 13:53:08 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/26 14:36:25 by jbouma        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	hook_controls(void *ptr)
{
	int				move;
	const int		moves[] = {'W', MLX_KEY_UP, 'A', MLX_KEY_LEFT,
		'D', MLX_KEY_RIGHT, 'S', MLX_KEY_DOWN, 0};
	const int		direction[] = {UP, LEFT, RIGHT, DOWN, HOLD};
	const t_game	*g = ptr;
	t_player		*p;

	p = g->player;
	p->is_moving = false;
	if (mlx_is_key_down(g->mlx, MLX_KEY_LEFT_SHIFT))
		p->jetpack = true;
	else
		p->jetpack = false;
	move = 0;
	while (moves[move])
	{
		if (mlx_is_key_down(g->mlx, moves[move]))
		{
			player_hook(ptr, direction[move / 2]);
			p->is_moving = true;
		}
		move++;
	}
	if (p->is_moving == false)
		player_hook(ptr, HOLD);
}
