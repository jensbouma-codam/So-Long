/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player_move.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/12 17:23:15 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/12 17:26:13 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	player_ml(void)
{
	ft_printf("Player moved left!\n");
	return (true);
}

bool	player_mu(void)
{
	ft_printf("Player moved up!\n");
	return (true);
}

bool	player_mr(void)
{
	ft_printf("Player moved right!\n");
	return (true);
}

bool	player_md(void)
{
	ft_printf("Player moved down!\n");
	return (true);
}

