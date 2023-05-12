/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/11 23:54:47 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/12 22:46:30 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

mlx_t	*g_mlx;
t_map	*g_maps;

void	map2console(void)
{
	t_element	*e;

	e = g_maps->element;
	while (e)
	{
		if (e->y == 0 && e->x == 0)
		{
			debug("Map name = %s\n", g_maps->name);
			debug("\nMap size = %i x %i\n", g_maps->width, g_maps->height);
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
	g_maps = (t_map *)safe_calloc(1, sizeof(*g_maps));
	g_maps->last_map = g_maps;
}

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
	initialize();
	load_files(argc, argv);
	map2console();
	if (!g_mlx)
		error("Initializing mlx failed");
	mlx_key_hook(g_mlx, &keyhooks, NULL);
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
	// 	initialize_window();
	// initalize_input();
	// 	initialize_camera();
	// 	initialize_keys();
	// 	initialize_mouse();
	// 	initialize_microphone();
	// initialize_game();
	// start_game();
