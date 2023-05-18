/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hook.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/12 13:53:08 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/18 14:33:07 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	hook_interface_keys(mlx_key_data_t keydata, void *param)
{	
	if (keydata.key == MLX_KEY_ESCAPE)
		hook_exit(param);
}

void	hook_player_keys(void *param)
{
	t_player	*p;
	int			move;
	int			trigger;
	const int	moves[] = {'W', MLX_KEY_UP, 'A', MLX_KEY_LEFT,
		'D', MLX_KEY_RIGHT, 'S', MLX_KEY_DOWN, 0};
	const int	direction[] = {UP, LEFT, RIGHT, DOWN, HOLD};

	p = (t_player *)param;
	trigger = HOLD;
	move = 0;
	while (moves[move])
	{
		if (mlx_is_key_down(g_mlx, moves[move]))
		{
			trigger = direction[move / 2];
			p->dir = trigger;
			hook_player(param);
		}
		move++;
	}
	p->dir = trigger;
}

void	hook_player(void *param)
{
	t_player	*p;

	p = (t_player *)param;
	if (p->state == STAND && p->dir == UP)
		p->trigger = JUMP;
	else if (p->jump_height == 0 && p->dir == DOWN)
		p->trigger = DUCK;
	else
		p->trigger = STAND;
	player_jump(p);
	player_fall(p);
	if (p->dir == LEFT)
	{
		p->trigger = WALK;
		if (p->x > 0)
			p->x -= 1;
	}
	else if (p->dir == RIGHT)
	{
		p->trigger = WALK;
		if (p->x + p->i->width + 4 < (unsigned int)g_mlx->width)
			p->x += 1;
	}
	player_update(param);
}

void	hook_exit(void *parm)
{
	game_exit(SIGINT);
}
