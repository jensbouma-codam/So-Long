/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/12 13:53:38 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/25 12:07:51 by jbouma        ########   odam.nl         */
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

void	*file_open(char **ptr, void *(f)(int fd, char *ptr))
{
	t_level	*node;
	t_level	*list;
	int		fd;

	list = NULL;
	while (*ptr)
	{
		debug("Load map file: %s\n", *ptr);
		fd = open(*ptr, O_RDONLY);
		if (fd != -1)
			node = f(fd, *ptr);
		else
			error(ft_strjoin("Failed to open file: ", *ptr));
		ptr++;
		close(fd);
		if (!list)
			list = node;
		else
		{
			node->prev = list;
			list->last->next = node;
		}
		list->last = node;
	}
	return (list);
}
