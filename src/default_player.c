/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   default_player.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/18 00:30:26 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/18 04:28:23 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_image	*default_player_walk(void)
{
	t_image		*i;
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

	return (files_texture_read((char **)files));
}

t_image	*default_player_stand(void)
{
	t_image		*i;
	const char	*files[] = {\
		"textures/Base pack/Player/p1_stand.png",
		NULL};

	return (files_texture_read((char **)files));
}

t_image	*default_player_duck(void)
{
	t_image		*i;
	const char	*files[] = {\
		"textures/Base pack/Player/p1_duck.png",
		NULL};

	return (files_texture_read((char **)files));
}

t_image	*default_player_jump(void)
{
	t_image		*i;
	const char	*files[] = {\
		"textures/Base pack/Player/p1_jump.png",
		NULL};

	return (files_texture_read((char **)files));
}

t_image	*default_player_hurt(void)
{
	t_image		*i;
	const char	*files[] = {\
		"textures/Base pack/Player/p1_hurt.png",
		NULL};

	return (files_texture_read((char **)files));
}
