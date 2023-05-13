/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/12 13:53:08 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/13 13:24:21 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	keyhooks(mlx_key_data_t keydata, void *param)
{	
	// const int	moves[] = {
	// 	'A', MLX_KEY_LEFT,
	// 	'W', MLX_KEY_UP,
	// 	'D', MLX_KEY_RIGHT,
	// 	'S', MLX_KEY_DOWN,
	// 	0};
	// const bool	(*move_f[])(void) = {
	// 	player_ml,
	// 	player_mu,
	// 	player_mr,
	// 	player_md
	// };

	int			move;

	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(g_mlx);
	// move = arr_position((int *)moves, keydata.key);
	// if (move != -1)
		// move_f[move / 2]();
}


void	loop(void *param)
{
	int			move;
	int			trigger;
	const int	moves[] = {
		'W', MLX_KEY_UP,
		'A', MLX_KEY_LEFT,
		'D', MLX_KEY_RIGHT,
		'S', MLX_KEY_DOWN,
		0};
	const int	direction[] = {
		UP,
		LEFT,
		RIGHT,
		DOWN,
		HOLD
	};

	trigger = HOLD;
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

static void	fall_hook()
{
	ft_printf("fall\n");
	if (g_player->x + g_img->img->height + 5 < g_mlx->height)
		g_player->y += 5;
	else
		g_player->y = g_mlx->height - g_img->img->height;
}

static void	jump_hook()
{
	if (g_player->state == JUMP && g_player->jump_state == STAND)
	{
		ft_printf("JUMP START\n");
		g_player->jump_state = JUMP;
		g_player->state = JUMP_TRUE;
		g_player->jump_height = 5;
	}
	if (g_player->jump_state == JUMP && g_player->y - 25 > 0 && g_player->jump_height < 250)
	{
		ft_printf("UP\n");
		g_player->y -= 25;
		g_player->jump_height += 25;
	}
	else if (g_player->jump_state == JUMP)
	{
		ft_printf("JUMP END\n");
		g_player->jump_state = FALL;
		g_player->jump_height = 0;
	}
	if (g_player->jump_state == FALL && g_player->y < g_mlx->height - g_img->img->height)
	{
		ft_printf("FALL\n");
		if (g_player->y + g_img->img->height + 5 < g_mlx->height)
			g_player->y += 5;
		else
		{
			ft_printf("FALL END\n");
			g_player->y = g_mlx->height - g_img->img->height;
			g_player->jump_state = STAND;
		}
	}
}

static update_player(void)
{
	g_img->img->instances[0].x = g_player->x;
	g_img->img->instances[0].y = g_player->y;
}

void	player_hook(void *param)
{
	(void)param;

	if (g_player->jump_state == STAND && g_player->direction == UP)
	{
		ft_printf("up\n");
		g_player->state = JUMP;
	}
	else if (g_player->jump_height == 0 && g_player->direction == DOWN)
		g_player->state = DUCK;
	jump_hook();
	if (g_player->direction == LEFT)
	{
		g_player->state = WALK;
		if (g_player->x > 0)
			g_player->x -= 5;
		ft_printf("left\n");
	}
	else if (g_player->direction == RIGHT)
	{
		g_player->state = WALK;
		if (g_player->x + g_img->img->width + 4 < g_mlx->width)
			g_player->x += 5;
		ft_printf("right\n");
	}
	update_player();
}

