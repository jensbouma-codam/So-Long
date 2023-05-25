/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   level.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/12 20:16:27 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/25 13:01:53 by jbouma        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	level_check(t_level *level)
{
	level_check_filename(level);
	level_check_elements(level);
	level_check_rectangular(level);
	level_check_surrounded(level);
	level_check_path(level);
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
	level_check(node);
	return (node);
}

t_level	*level_default(void)
{
	t_level		*level;
	const char	*files[] = {\
		"./maps/valid_small.ber",
		"./maps/valid_subject.ber",
		NULL};

	print("No arguments given. Loading default maps...\n");
	level = file_open((char **)files, level_read);
	return (level);
}

t_image	*level_textures(t_game *game)
{
	const char	*files[] = {
		"textures/Base pack/Items/coinGold.png",
		"textures/Base pack/Items/coinGold.png",
		"textures/Base pack/Tiles/door_openMid.png",
		"textures/Base pack/Tiles/door_closedMid.png",
		"textures/Base pack/Tiles/castleCenter.png",
		"textures/Base pack/Tiles/grassCenter.png",
		NULL};

	return (texture_read_files(game, (char **)files, 1));
}
