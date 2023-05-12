/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player_move.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/12 17:23:15 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/12 18:57:25 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

const bool	player_ml(void)
{
	ft_printf("Player moved left!\n");
	return (true);
}

const bool	player_mu(void)
{
	ft_printf("Player moved up!\n");
	return (true);
}

const bool	player_mr(void)
{
	ft_printf("Player moved right!\n");
	return (true);
}

const bool	player_md(void)
{
	ft_printf("Player moved down!\n");
	return (true);
}
