/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/11 23:54:47 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/18 19:47:43 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int	main(int argc, char **argv)
{
	t_game		*game;	
	t_player	*p;

	game = default_init(argc, argv);
	map_draw(&game);
	player_init(game->player);
	mlx_loop(g_mlx);
	return (EXIT_FAILURE);
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
