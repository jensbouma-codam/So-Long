/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/11 23:54:47 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/13 13:00:19 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

mlx_t		*g_mlx;
t_map		*g_map;
t_images	*g_img;
t_player	*g_player;

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

void	initialize(void)
{
	g_mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	g_map = (t_map *)safe_calloc(1, sizeof(*g_map));
	g_player = (t_player *)safe_calloc(1, sizeof(*g_player));
	g_player->jump_state = FALL;
	g_map->last_map = g_map;
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
	initialize();
	load_files(argc, argv);
	map2console();
	if (!g_mlx)
		error("Initializing mlx failed");
	mlx_image_to_window(g_mlx, g_img->img, 0, 0);
	mlx_image_to_window(g_mlx, g_img->next->img, 0, 0);
	g_img->next->img->instances->enabled = false;
	// mlx_key_hook(g_mlx, &keyhooks, NULL);
	mlx_loop_hook(g_mlx, &player_hook, NULL);
	mlx_loop_hook(g_mlx, &loop, g_mlx);
	// mlx_loop_hook(g_mlx, &jump_hook, g_mlx);
	mlx_loop(g_mlx);

	mlx_terminate(g_mlx);
	console("Thanks for playing! Check https:/jensbouma.com \
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
