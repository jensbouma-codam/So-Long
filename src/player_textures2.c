/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player_textures2.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbouma <jbouma@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/31 17:10:08 by jbouma        #+#    #+#                 */
/*   Updated: 2023/06/01 12:32:03 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_image	*player_texture_jetpack(t_game *g)
{
	const char	*files[] = {\
		"textures/Base pack/Items/cloud3.png", \
		NULL};

	return (texture_read_files(g, (char **)files, 0.5));
}
