/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/18 11:45:46 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/18 23:30:11 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	game_exit(int sig)
{
	if (sig == SIGINT)
	{
		console_log("Thanks for playing! Check https:/jensbouma.com if you like \
		for my other projects! :)\n");
		mlx_terminate(g_mlx);
		system("leaks so_long");
		exit(EXIT_SUCCESS);
	}
}

double	game_window(t_map *map)
{
	int32_t	display_x;
	int32_t	display_y;
	double	size;
	double	scale;

	size = 70;
	scale = size;
	mlx_get_monitor_size(0, &display_x, &display_y);
	if (!display_x || !display_y)
	{
		display_x = 1920;
		display_y = 1080;
	}
	display_x -= 100;
	display_y -= 100;
	while ((size * map->width) < display_x && (size * map->height) < display_y)
		size += 1;
	while ((size * map->width) > display_x || (size * map->height) > display_y)
		size -= 1;
	mlx_set_window_size(g_mlx, size * map->width, size * map->height);
	mlx_set_window_pos(g_mlx,
		((display_x + 100) / 2) - (size * map->width) / 2,
		((display_y + 100) / 2) - (size * map->height / 2));
	return (size / scale);
}
