/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hook.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/12 13:53:08 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/18 04:43:07 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	hook_keys(mlx_key_data_t keydata, void *param)
{	
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(param);
}

void	hook_action(void *param)
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
			console_log("Player Direction = %d", p->dir);
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
	if (p->jump_state == STAND && p->dir == UP)
		p->action = JUMP;
	else if (p->jump_height == 0 && p->dir == DOWN)
		p->action = DUCK;
	player_jump(p);
	player_fall(p);
	if (p->dir == LEFT)
	{
		p->action = WALK;
		if (p->x > 0)
			p->x -= 5;
	}
	else if (p->dir == RIGHT)
	{
		p->action = WALK;
		if (p->x + p->stand->mlx_image->width + 4 < (unsigned int)g_mlx->width)
			p->x += 5;
	}
	ft_printf("Player Direction = %d\n", p->dir);
	player_update(param);
}
