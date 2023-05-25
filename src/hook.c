/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hook.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/12 13:53:08 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/26 00:45:40 by jensbouma     ########   odam.nl         */
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
	const int		moves[] = {'W', MLX_KEY_UP, 'A', MLX_KEY_LEFT,
		'D', MLX_KEY_RIGHT, 'S', MLX_KEY_DOWN, 0};
	const int		direction[] = {UP, LEFT, RIGHT, DOWN, HOLD};
	const t_game	*g = ptr;
	t_player		*p;

	p = g->player;
	p->dir = HOLD;
	move = 0;
	if (mlx_is_key_down(g->mlx, MLX_KEY_LEFT_SHIFT))
		p->jetpack = true;
	else if (p->jetpack == true)
	{
		p->jetpack = false;
		p->state = FALL;
	}
	while (moves[move])
	{
		if (mlx_is_key_down(g->mlx, moves[move]))
			p->dir = direction[move / 2];
		move++;
	}
}
