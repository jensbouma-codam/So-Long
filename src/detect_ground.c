/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   detect_ground.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/01 11:12:47 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/06/01 11:54:12 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	detect_ground(t_game *game)
{
	t_player	*p;

	p = game->player;
	p->y += 3;
	if (detect_hook(game))
	{
		p->y -= 3;
		return (true);
	}
	p->y -= 3;
	return (false);
}
