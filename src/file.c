/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/12 13:53:38 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/21 15:30:42 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

char	*file_getname(char *ptr)
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

void	*file_readmap(int fd, char *ptr)
{
	int			y;
	char		*line;
	t_map		*node;

	y = 0;
	node = (t_map *)memmory_alloccate(1, sizeof(*node));
	node->name = file_getname(ptr);
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

void	*file_open(char **ptr, void *(f)(int fd, char *ptr))
{
	t_map	*node;
	t_map	*list;
	int		fd;

	list = NULL;
	while (*ptr)
	{
		console_debug("Open file: %s\n", *ptr);
		fd = open(*ptr, O_RDONLY);
		if (fd != -1)
			node = f(fd, *ptr);
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

static	mlx_image_t	*file_readpng_resize(mlx_t *mlx, char *file, double s)
{
	mlx_texture_t	*t;
	mlx_image_t		*i;

	t = mlx_load_png(file);
	if (!t)
		console_error(ft_strjoin("Failed to load texture: ", file));
	i = mlx_texture_to_image(mlx, t);
	mlx_delete_texture(t);
	if (!i)
		console_error(ft_strjoin("Failed to load texture: ", file));
	if (s != 1)
		mlx_resize_image(i, i->width * s, i->height * s);
	return (i);
}

t_image	*file_readimage(t_game *g, char **ptr, double scale)
{
	t_image			*list;
	t_image			*node;

	list = NULL;
	while (*ptr)
	{
		node = (t_image *)memmory_alloccate(1, sizeof(*node));
		console_debug("Loading texture: %s\n", *ptr);
		node->mlx_image = file_readpng_resize(g->mlx, *ptr, scale * g->scale);
		if (!node->mlx_image)
			console_error(ft_strjoin("Failed to load texture: ", *ptr));
		mlx_image_to_window(g->mlx, node->mlx_image, 0, 0);
		node->mlx_image->instances->enabled = false;
		node->name = file_getname(*ptr);
		node->next = NULL;
		node->firstrun = true;
		node->frame_delay = 0;
		if (list)
			node->next = list;
		list = node;
		ptr++;
	}
	return (list);
}
