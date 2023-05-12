/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handler.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/12 17:51:59 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/12 18:14:33 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>

void	error(char *msg)
{
	if (g_mlx)
	{
		puts(mlx_strerror(mlx_errno));
		ft_printf("Terminating mlx\n");
		mlx_terminate(g_mlx);
	}
	write(STDERR_FILENO, "Error\n", 6);
	perror(msg);
	exit (EXIT_FAILURE);
}
