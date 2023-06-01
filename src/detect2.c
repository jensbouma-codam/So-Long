/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   detect2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/01 11:12:47 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/06/01 16:22:40 by jbouma        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	detect_ground(t_game *game)
{
	t_player	*p;
	uint32_t	offset;

	p = game->player;
	offset = 3 * game->scale;
	p->y += offset;
	if (detect_hook(game))
	{
		p->y -= offset;
		return (true);
	}
	p->y -= offset;
	return (false);
}
