/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/18 11:45:46 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/18 14:38:16 by jensbouma     ########   odam.nl         */
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
