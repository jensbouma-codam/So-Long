/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/11 23:54:47 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/16 23:16:29 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

void	map2console(void)
{
	t_element	*e;

	e = g_map->element;
	while (e)
	{
		if (e->y == 0 && e->x == 0)
		{
			debug("Map name = %s\n", g_map->name);
			debug("\nMap size = %i x %i\n", g_map->width, g_map->height);
		}
		debug("%c", e->type);
		if (e->next && e->next->y > e->y)
			debug("\n");
		e = e->next;
	}
}

/**
 * @brief 
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int	main(int argc, char **argv)
{
	init_globals();
	load_files(argc, argv);
	map2console();
	if (!g_mlx)
		error("Initializing mlx failed");
	mlx_image_to_window(g_mlx, g_img->img, 0, 0);
	mlx_image_to_window(g_mlx, g_img->next->img, 0, 0);
	g_img->next->img->instances->enabled = false;
	mlx_loop_hook(g_mlx, &player_hook, g_mlx);
	mlx_loop_hook(g_mlx, &action_hook, g_mlx);
	mlx_loop(g_mlx);
	mlx_terminate(g_mlx);
	console("Thanks for playing! Check https:/jensbouma.com if you like \
	for my other projects! :)\n");
	return (EXIT_SUCCESS);
}

	// load_textures();
	// 	load_maps();
	// 		test_map();
	// 			count_elements();
	// 			is_valid_map();
	// 			is_playable();
	// initalize_output();
	// 	initialize_debug();
	// 	initialize_math();
	// 	initialize_speaker();
	// 	initalize_gui();
	// initalize_input();
	// 	initialize_camera();
	// 	initialize_keys();
	// 	initialize_mouse();
	// 	initialize_microphone();
	// initialize_game();
	// start_game();
