/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   console.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/12 17:51:59 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/21 15:28:38 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "colors.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>

static void	console_print(const char *s, va_list list)
{
	while (*s)
	{
		if (*s == '%' && *s++ && *s != '%')
		{
			if (*s == 'c' || *s == 'd' || *s == 'i'
				|| *s == 'u' || *s == 'x' || *s == 'X')
				process_int(*s, va_arg(list, int));
			else if (*s == 's' || *s == 'p')
				process_char(*s, va_arg(list, char *));
		}
		else
			ft_putchar_fd(*s, STDOUT_FILENO);
		s++;
	}
}

void	console_error(char *msg)
{
	write(STDERR_FILENO, "Error\n", 6);
	if (msg)
		perror(msg);
	exit (EXIT_FAILURE);
}

void	console_log(const char *s, ...)
{
	va_list	list;

	va_start(list, s);
	console_print(s, list);
	va_end(list);
}

void	console_debug(const char *s, ...)
{
	va_list	list;

	if (DEBUG == 0)
		return ;
	ft_printf("%s", YELLOW);
	va_start(list, s);
	console_print(s, list);
	ft_printf("%s", NORMAL);
	va_end(list);
}

void	console_print_map(t_map *map)
{
	t_tiles	*e;

	while (map)
	{
		console_log("Map name = %s\n", map->name);
		console_log("\nMap size = %i x %i\n", map->width, map->height);
		e = map->tiles;
		while (e)
		{
			console_log("%c", e->type);
			if (e->next && e->next->y > e->y)
				console_log("\n");
			e = e->next;
		}
		console_log("\n");
		map = map->next;
	}
}
