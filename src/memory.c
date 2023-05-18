/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   memory.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 22:51:00 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/17 22:52:48 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*memmory_alloccate(size_t count, size_t size)
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
			console_error("Memmory allocation failed");
		}
	}
	ft_bzero(ptr, size * count);
	return (ptr);
}
