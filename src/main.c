/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/11 23:54:47 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/12 18:18:51 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
// #include "/opt/homebrew/Cellar/glfw/3.3.8/include/GLFW/glfw3.h"

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

mlx_t	*g_mlx;

/**
 * @brief 
• open, close, read, write, malloc, free, perror, strerror, exit
• All functions of the math library (-lm compiler option, man man 3 math)
• All functions of the MiniLibX
• ft_printf and any equivalent YOU coded
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int	main(int argc, char **argv)
{
	if (argc > 1)
	{
		read_files(argv + 1, load_map_files);
		load_defaults(ONLY_TEXTURES);
	}
	else if (argc == 1)
	{
		ft_printf("No arguments given, loading defaults!\n");
		load_defaults(MAPS);
	}
	ft_printf("Done loading files!\n");
	g_mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!g_mlx)
		error("Initializing mlx failed");
	mlx_key_hook(g_mlx, &keyhooks, NULL);
	mlx_loop(g_mlx);
	mlx_terminate(g_mlx);
	ft_printf("Thanks for playing! Check https:/jensbouma.com \
	for my other projects! :)\n");
	return (EXIT_SUCCESS);

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
	// 	initialize_window();
	// initalize_input();
	// 	initialize_camera();
	// 	initialize_keys();
	// 	initialize_mouse();
	// 	initialize_microphone();
	// initialize_game();
	// start_game();
}
