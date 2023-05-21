/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   console.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/12 17:51:59 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/21 15:54:42 by jensbouma     ########   odam.nl         */
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

void	console_error_exit(char *msg)
{
	ft_putstr_fd(RED, STDERR_FILENO);
	write(STDERR_FILENO, "Error\n", 6);
	if (msg)
		perror(msg);
	ft_putstr_fd(NORMAL, STDERR_FILENO);
	exit (EXIT_FAILURE);
}

void	console_error(const char *s, ...)
{
	va_list	list;

	ft_putstr_fd(RED, STDERR_FILENO);
	write(STDERR_FILENO, "Error\n", 6);
	va_start(list, s);
	console_print(s, list);
	ft_putstr_fd(NORMAL, STDERR_FILENO);
	va_end(list);
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
	ft_putstr_fd(YELLOW, STDOUT_FILENO);
	va_start(list, s);
	console_print(s, list);
	ft_putstr_fd(NORMAL, STDOUT_FILENO);
	va_end(list);
}
