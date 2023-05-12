/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   maps.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/12 20:16:27 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/12 22:41:11 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	process_map(char *line, int y)
{
	t_element			*element;
	int					x;

	x = 0;
	while (line[x] != '\0' && line[x] != '\n')
	{
		element = (t_element *)safe_calloc(1, sizeof(*element));
		element->type = line[x];
		element->x = x;
		element->y = y;
		if (!g_maps->element)
			g_maps->element = element;
		else
		{
			element->prev = g_maps->element;
			g_maps->last_element->next = element;
			g_maps->last_element->next = element;
		}
		g_maps->last_element = element;
		x++;
	}
	g_maps->width = x - 1;
	g_maps->height = y;
}

// Check if map is rectangular
// Check if map has all elements
// Check if map has valid elements
// Check if map has valid amount of elements
// Check if map has valid amount of collectibles
// Check if map has valid amount of exits
// Check if map has valid amount of players
// Check if map has valid amount of walls
// Check if map has valid amount of empty spaces
// Check if map has valid amount of enemies
void	check_maps(void)
{
}

void	load_map_files(int fd, char *ptr)
{
	char	*line;
	int		y;

	y = 0;
	debug("Loading mapfile: %s\n", ptr);
	line = get_next_line(fd);
	if (!line)
		error(ft_strjoin("Failed to read map: ", ptr));
	while (line)
	{
		process_map(line, y++);
		free(line);
		line = get_next_line(fd);
	}
	g_maps->last_map->name = get_filename(ptr);
	check_maps();
	y = 0;
}
