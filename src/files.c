/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   files.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/12 13:53:38 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/12 18:29:49 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

void	read_files(char **ptr, void (*func)(int, char *))
{
	int			fd;

	while (*ptr)
	{
		fd = open(*ptr, O_RDONLY);
		if (fd != -1)
			func(fd, *ptr);
		else
			error("Opening file failed");
		ptr++;
	}
}

void	load_map_files(int fd, char *ptr)
{
	char	*line;

	ft_printf("Loading mapfile: %s\n", ptr);
	line = get_next_line(fd);
	if (!line)
		error(ft_strjoin("Failed to read map: ", ptr));
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}

void	load_texture_files(int fd, char *ptr)
{
	char	*line;

	ft_printf("Loading texture: %s\n", ptr);
	line = get_next_line(fd);
	if (!line)
		error(ft_strjoin("Failed to read texture: ", ptr));
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}
