/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/11 23:54:47 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/06/01 16:39:11 by jbouma        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int	main(int argc, char **argv)
{
	t_game		*game;

	errno = 0;
	game = game_init(argc, argv);
	if (NOMLX)
		return (EXIT_SUCCESS);
	mlx_loop(game->mlx);
	if (DEBUG && system("leaks so_long"))
		exit(EXIT_FAILURE);
	exit (EXIT_FAILURE);
}
