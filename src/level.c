/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   level.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/12 20:16:27 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/06/01 11:49:47 by jensbouma     ########   odam.nl         */
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
		{
			level->c_player++;
			tile->reachable = true;
		}
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

static void	level_process_line(t_level *level, char *line, int y)
{
	t_tiles	*t;
	int		x;

	x = 0;
	errno = 0;
	if (line[0] == '\0' || line[0] == '\n')
		error("Empty line in level");
	while (line[x] != '\0' && line[x] != '\n')
	{
		t = (t_tiles *)memmory_alloccate(1, sizeof(*t));
		t->type = line[x];
		t->x = x;
		t->y = y;
		if (!level->tile)
			level->tile = t;
		else
		{
			t->prev = level->tile;
			level->tile_last->next = t;
		}
		level->tile_last = t;
		x++;
	}
	level->w = x;
	level->h = y + 1;
}

void	*level_read(int fd, char *ptr)
{
	int			y;
	char		*line;
	t_level		*node;

	y = 0;
	node = (t_level *)memmory_alloccate(1, sizeof(*node));
	node->c_collectible = 0;
	node->c_empty = 0;
	node->c_exit = 0;
	node->c_player = 0;
	node->c_wall = 0;
	node->name = file_getname(ptr);
	line = get_next_line(fd);
	if (!line)
		error(ft_strjoin("Failed to read level: ", ptr));
	while (line)
	{
		debug("line: %s\n", line);
		level_process_line(node, line, y++);
		free(line);
		line = get_next_line(fd);
	}
	level_count_elements(node);
	level_check(node);
	return (node);
}

t_level	*level_default(void)
{
	t_level		*level;
	const char	*files[] = {\
		"./maps/valid_platform.ber",
		"./maps/valid_small.ber",
		NULL};

	print("No arguments given. Loading default maps...\n");
	level = file_open((char **)files, level_read);
	return (level);
}

t_image	*level_textures(t_game *game)
{
	const char	*files[] = {
		// "textures/Base pack/Items/coinGold.png",
		"textures/Base pack/Items/keyYellow.png",
		"textures/Base pack/Tiles/door_openMid.png",
		"textures/Base pack/Tiles/door_closedMid.png",
		"textures/Base pack/Tiles/castleCenter.png",
		"textures/Base pack/Tiles/liquidWater.png",
		// "textures/Base pack/Tiles/grassCenter.png",
		NULL};

	return (texture_read_files(game, (char **)files, 1));
}
