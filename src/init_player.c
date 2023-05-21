/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_player.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/18 00:30:26 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/21 18:21:54 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_image	*init_player_stand(t_game *g)
{
	const char	*files[] = {\
		"textures/Base pack/Player/p1_stand.png",
		NULL};

	return (file_readimage(g, (char **)files, 0.5));
}

t_image	*init_player_walk(t_game *g)
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

	return (file_readimage(g, (char **)files, 0.5));
}

t_image	*init_player_duck(t_game *g)
{
	const char	*files[] = {\
		"textures/Base pack/Player/p1_duck.png",
		NULL};

	return (file_readimage(g, (char **)files, 0.5));
}

t_image	*init_player_jump(t_game *g)
{
	const char	*files[] = {\
		"textures/Base pack/Player/p1_jump.png",
		NULL};

	return (file_readimage(g, (char **)files, 0.5));
}

t_image	*init_player_hurt(t_game *g)
{
	const char	*files[] = {\
		"textures/Base pack/Player/p1_hurt.png",
		NULL};

	return (file_readimage(g, (char **)files, 0.5));
}
