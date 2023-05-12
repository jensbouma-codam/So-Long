/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handler.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/12 17:51:59 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/12 22:47:02 by jensbouma     ########   odam.nl         */
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

void	error(char *msg)
{
	if (g_mlx)
	{
		ft_printf(mlx_strerror(mlx_errno));
		mlx_terminate(g_mlx);
	}
	write(STDERR_FILENO, "Error\n", 6);
	perror(msg);
	exit (EXIT_FAILURE);
}

void	console(const char *s, ...)
{
	va_list	list;

	va_start(list, s);
	console_print(s, list);
	va_end(list);
}

void	debug(const char *s, ...)
{
	va_list	list;

	if (!DEBUG)
		return ;
	ft_printf("%s", YELLOW);
	va_start(list, s);
	console_print(s, list);
	ft_printf("%s", NORMAL);
	va_end(list);
}

void	*safe_calloc(size_t count, size_t size)
{
	int		tries;
	void	*ptr;

	tries = 0;
	while (true)
	{
		ptr = malloc(size * count + 1);
		if (ptr)
			break ;
		if (tries++ == 9)
		{
			error("Memmory allocation failed");
		}
	}
	ft_bzero(ptr, size * count);
	return (ptr);
}
