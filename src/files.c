/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   files.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/12 13:53:38 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/18 23:17:59 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

t_map	*files_read_map(int fd, char *ptr)
{
	int			y;
	char		*line;
	t_map		*node;

	y = 0;
	node = (t_map *)memmory_alloccate(1, sizeof(*node));
	node->name = files_get_filename(ptr);
	line = get_next_line(fd);
	if (!line)
		console_error(ft_strjoin("Failed to read map: ", ptr));
	while (line)
	{
		map_add(node, line, y++);
		free(line);
		line = get_next_line(fd);
	}
	return (node);
}

t_map	*files_open_map(char **ptr)
{
	t_map	*node;
	t_map	*list;
	int		fd;

	list = NULL;
	while (*ptr)
	{
		console_debug("Loading map: %s\n", *ptr);
		fd = open(*ptr, O_RDONLY);
		if (fd != -1)
			node = files_read_map(fd, *ptr);
		else
			console_error(ft_strjoin("Failed to open file: ", *ptr));
		ptr++;
		close(fd);
		if (list)
			node->next = list;
		list = node;
	}
	return (list);
}

static	mlx_image_t	*resize(mlx_image_t *i, double scale)
{
	if (scale == 1)
		return (i);
	mlx_resize_image(i, i->width * scale, i->height * scale);
	return (i);
}

t_image	*files_texture_read(char **ptr, double scale)
{
	mlx_texture_t	*mlx_texture;
	t_image			*list;
	t_image			*node;

	list = NULL;
	while (*ptr)
	{
		node = (t_image *)memmory_alloccate(1, sizeof(*node));
		console_debug("Loading texture: %s\n", *ptr);
		mlx_texture = mlx_load_png(*ptr);
		if (!mlx_texture)
			console_error(ft_strjoin("Failed to load texture: ", *ptr));
		node->mlx_image = resize(
				mlx_texture_to_image(g_mlx, mlx_texture), scale);
		mlx_delete_texture(mlx_texture);
		if (!node->mlx_image)
			console_error(ft_strjoin("Failed to load texture: ", *ptr));
		node->name = files_get_filename(*ptr);
		node->next = NULL;
		if (list)
			node->next = list;
		list = node;
		ptr++;
	}
	return (list);
}

char	*files_get_filename(char *ptr)
{
	char	*filename;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (ptr[i] != '\0')
	{
		if (ptr[i] == '/')
			j = i + 1;
		i++;
	}
	filename = ft_substr(ptr, j, i);
	return (filename);
}
