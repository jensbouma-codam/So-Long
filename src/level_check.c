/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   level_check.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/25 10:13:00 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/25 12:51:49 by jbouma        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	level_count_elements(t_level *level)
{
	t_tiles	*tile;

	tile = level->tile;
	while (tile)
	{
		if (tile->type == 'P')
			level->c_player++;
		else if (tile->type == 'E')
			level->c_exit++;
		else if (tile->type == '1')
			level->c_wall++;
		else if (tile->type == '0')
			level->c_empty++;
		else if (tile->type == 'C')
			level->c_collectible++;
		else
			error("Invalid element in level");
		tile = tile->next;
	}
}

// check if the filename is valid
void	level_check_filename(t_level *level)
{
	char	*ext;

	errno = 0;
	ext = ft_substr(level->name, ft_strlen(level->name) - 4, 4);
	if (ft_strstr(ext, ".ber") == NULL)
		error(ft_strjoin("Invalid extention in filename: ", level->name));
	(void)level;
}

void	level_check_elements(t_level *level)
{	
	level_count_elements(level);
	if (level->c_player != 1)
		error("There should be exactly one player");
	if (level->c_exit != 1)
		error("There should be at least one exit");
	if (level->c_wall < 12)
		error("There should be at least 12 walls");
	if (level->c_collectible < 1)
		error("There should be at least one collectible");

}

// check if the level is rectangular
void	level_check_rectangular(t_level *level)
{
	(void)level;
}

// check if the level is surrounded by walls
void	level_check_surrounded(t_level *level)
{
	(void)level;
}

// check if there is a path from the player to the exit
void	level_check_path(t_level *level)
{
	(void)level;
}
