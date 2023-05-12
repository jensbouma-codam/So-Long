/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   files.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/12 13:53:38 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/12 22:41:05 by jensbouma     ########   odam.nl         */
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
		"./textures/test2.txt",
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
	char	*line;

	debug("Loading texture: %s\n", ptr);
	line = get_next_line(fd);
	if (!line)
		error(ft_strjoin("Failed to read texture: ", ptr));
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
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
