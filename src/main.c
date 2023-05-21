/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/11 23:54:47 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/21 23:06:04 by jensbouma     ########   odam.nl         */
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

	game = init_game(argc, argv);
	mlx_loop(game->mlx);
	return (EXIT_FAILURE);
}

	// 		test_map();
	// 			count_elements();
	// 			is_valid_map();
	// 			is_playable();
