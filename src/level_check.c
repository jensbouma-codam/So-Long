/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   level_check.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/25 10:13:00 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/26 14:21:37 by jbouma        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// check if the filename is valid
void	level_check_filename(t_level *level)
{
	char	*ext;

	errno = 0;
	ext = ft_substr(level->name, ft_strlen(level->name) - 4, 4);
	if (ft_strstr(ext, ".ber") == NULL)
		error(ft_strjoin("Invalid extention in filename: ", level->name));
	free(ext);
}

void	level_check_elements(t_level *level)
{	
	if (level->c_player != 1)
		error("There should be exactly one player");
	if (level->c_exit != 1)
		error("There should be exactly one exit");
	if (level->c_wall < 12)
		error("There should be at least 12 walls");
	if (level->c_collectible < 1)
		error("There should be at least one collectible");
}

// check if the level is surrounded by walls
void	level_check_surrounded(t_level *level)
{
	t_tiles	*tile;

	tile = level->tile;
	while (tile)
	{
		if (tile->type != WALL)
		{
			if (tile->x == 0)
				error("Missing element in left wall");
			if (tile->y == 0)
				error("Missing element in top wall");
			if (tile->x == level->w - 1)
				error("Missing element in right wall");
			if (tile->y == level->h - 1)
				error("Missing element in bottom wall");
		}
		tile = tile->next;
	}
}

// check if the level is rectangular
void	level_check_rectangular(t_level *level)
{
	t_tiles		*tile;
	uint32_t	w;

	tile = level->tile;
	w = level->w;
	while (tile)
	{
		if (tile->next && tile->next->y > tile->y)
		{
			if (tile->x != level->w - 1 || tile->x != w - 1)
				error("The level is not rectangular");
			w = tile->x + 1;
		}
		tile = tile->next;
	}
}

void	level_check(t_level *level)
{
	level_check_filename(level);
	level_check_elements(level);
	level_check_rectangular(level);
	level_check_surrounded(level);
	level_check_path(level);
}
