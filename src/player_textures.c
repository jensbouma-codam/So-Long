/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player_textures.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/18 00:30:26 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/31 17:14:16 by jbouma        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_image	*player_texture_stand(t_game *g)
{
	const char	*files[] = {\
		"textures/Base pack/Player/p1_stand.png",
		NULL};

	return (texture_read_files(g, (char **)files, 0.3));
}

t_image	*player_texture_walk(t_game *g)
{
	const char	*files[] = {\
		"textures/Base pack/Player/p1_walk/PNG/p1_walk01.png",
		"textures/Base pack/Player/p1_walk/PNG/p1_walk02.png",
		"textures/Base pack/Player/p1_walk/PNG/p1_walk03.png",
		"textures/Base pack/Player/p1_walk/PNG/p1_walk04.png",
		"textures/Base pack/Player/p1_walk/PNG/p1_walk05.png",
		"textures/Base pack/Player/p1_walk/PNG/p1_walk06.png",
		"textures/Base pack/Player/p1_walk/PNG/p1_walk07.png",
		"textures/Base pack/Player/p1_walk/PNG/p1_walk08.png",
		"textures/Base pack/Player/p1_walk/PNG/p1_walk09.png",
		"textures/Base pack/Player/p1_walk/PNG/p1_walk10.png",
		"textures/Base pack/Player/p1_walk/PNG/p1_walk11.png",
		NULL};

	return (texture_read_files(g, (char **)files, 0.3));
}

t_image	*player_texture_duck(t_game *g)
{
	const char	*files[] = {\
		"textures/Base pack/Player/p1_duck.png",
		NULL};

	return (texture_read_files(g, (char **)files, 0.3));
}

t_image	*player_texture_jump(t_game *g)
{
	const char	*files[] = {\
		"textures/Base pack/Player/p1_jump.png",
		NULL};

	return (texture_read_files(g, (char **)files, 0.3));
}

t_image	*player_texture_hurt(t_game *g)
{
	const char	*files[] = {\
		"textures/Base pack/Player/p1_hurt.png",
		NULL};

	return (texture_read_files(g, (char **)files, 0.3));
}
