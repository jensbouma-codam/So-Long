/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   globals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/15 11:10:15 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/16 15:51:02 by jbouma        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_images	*g_img;
t_map		*g_map;
t_player	*g_player;
mlx_t		*g_mlx;

void	init_globals(void)
{
	g_mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	g_map = (t_map *)safe_calloc(1, sizeof(*g_map));
	g_player = (t_player *)safe_calloc(1, sizeof(*g_player));
	g_player->jump_state = FALL;
	g_map->last_map = g_map;
}
