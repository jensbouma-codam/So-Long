/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   maps.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/12 20:16:27 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/18 04:29:37 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_add(t_map *map, char *line, int y)
{
	t_element			*element;
	int					x;

	x = 0;
	while (line[x] != '\0' && line[x] != '\n')
	{
		element = (t_element *)memmory_alloccate(1, sizeof(*element));
		element->type = line[x];
		element->x = x;
		element->y = y;
		if (!map->element)
			map->element = element;
		else
		{
			element->prev = map->element;
			map->last_element->next = element;
			map->last_element->next = element;
		}
		map->last_element = element;
		x++;
	}
	map->width = x;
	map->height = y + 1;
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
