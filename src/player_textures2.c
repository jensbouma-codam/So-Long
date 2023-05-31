/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player_textures2.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbouma <jbouma@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/31 17:10:08 by jbouma        #+#    #+#                 */
/*   Updated: 2023/05/31 17:10:57 by jbouma        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_image	*player_texture_jetpack(t_game *g)
{
	const char	*files[] = {\
		"textures/Request pack/Tiles/laserBlueBurst.png", \
		NULL};

	return (texture_read_files(g, (char **)files, 0.5));
}
