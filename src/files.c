/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   files.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/12 13:53:38 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/13 02:59:53 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

void	load_files(int argc, char **argv)
{
	const char	*maps[] = {\
		"./maps/valid.ber",
		NULL};
	const char	*textures[] = {\
		"textures/Base pack/Tiles/grass.png",
		"textures/Base pack/Tiles/stoneCenter_rounded.png",
		"textures/Base pack/Player/p1_stand.png",
		"textures/Base pack/Player/p1_jump.png",
		NULL};

	if (argc > 1)
		read_files((char **)argv + 1, load_map_files);
	else
	{
		console("No arguments given. Loading default maps...\n");
		read_files((char **)maps, load_map_files);
	}
	read_files((char **)textures, load_texture_files);
	debug("Done loading files!\n");
}

void	read_files(char **ptr, void (*func)(int, char *))
{
	int			fd;

	while (*ptr)
	{
		fd = open(*ptr, O_RDONLY);
		if (fd != -1)
			func(fd, *ptr);
		else
			error(ft_strjoin("Failed to open file: ", *ptr));
		ptr++;
	}
}

void	load_texture_files(int fd, char *ptr)
{
	mlx_image_t		*image;
	t_images		*node;

	image = NULL;
	debug("Loading texture: %s\n", ptr);
	node = (t_images *)safe_calloc(1, sizeof(*g_img));
	image = mlx_texture_to_image(g_mlx, mlx_load_png(ptr));
	if (!image)
		error(ft_strjoin("Failed to load texture: ", ptr));
	if (g_img)
	{
		g_img->prev = node;
		node->next = g_img;
	}
	node->name = get_filename(ptr);
	node->img = image;
	node->prev = NULL;
	g_img = node;
}

char	*get_filename(char *ptr)
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
