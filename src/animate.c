/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   animation.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/21 14:36:10 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/21 14:47:06 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_image	*animate(t_image *a, t_image *i)
{
	if (i->firstrun)
		return ((i->firstrun = false), i);
	if (i->frame_delay == 0)
	{
		i->frame_delay = 10;
		if (a->next)
			a = a->next;
		else
			a = i;
	}
	else
		i->frame_delay--;
	return (a);
}
