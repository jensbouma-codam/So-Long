/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/11 23:54:47 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/18 04:44:41 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

// void	load_image(t_image *i)
// {

// 	// while (i->name)
// 	// {
// 	// 	console_log("Try");
// 	// 	console_log("Loading image: %s\n", i->name);
// 	// 	console_log("Loading NEXT image: %p\n", i->next);
// 	// 	mlx_image_to_window(g_mlx, i->mlx_image, 1, 1);
// 	// 	if (!i->next)
// 	// 		break ;
// 	// 	i = i->next;
// 	// }
// }

// void	draw_player(t_game *game)
// {
// 	load_image(game->player->walk);
// }

// static void preload_textures(t_game *game)
// {
// 	// draw_map(game);
// 	draw_player(game);
// 	// draw_exit(game);
// 	// draw_collectibles(game);
// }

/**
 * @brief 
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int	main(int argc, char **argv)
{
	t_game		*game;	
	t_player	*p;

	game = default_init(argc, argv);
	console_print_map(game->map);
	p = game->player;
	mlx_image_to_window(g_mlx, game->image->mlx_image, 0, 0);
	mlx_image_to_window(g_mlx, p->walk->mlx_image, p->x, p->y);
	mlx_image_to_window(g_mlx, p->stand->mlx_image, 80, 0);
	mlx_loop_hook(g_mlx, &hook_player, game->player);
	mlx_loop_hook(g_mlx, &hook_action, game->player);
	mlx_loop(g_mlx);
	mlx_terminate(g_mlx);
	console_log("Thanks for playing! Check https:/jensbouma.com if you like \
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
