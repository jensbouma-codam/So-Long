/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/18 23:21:05 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/18 23:25:42 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	hit_object(t_player *p, t_listner *l)
{
	if ((p->x >= l->x && p->x < l->x + l->i->width
			|| p->x + p->i->width >= l->x
			&& p->x + p->i->width <= l->x + l->i->width)
		&& (p->y >= l->y && p->y <= l->y + l->i->height
			|| p->y + p->i->height >= l->y
			&& p->y + p->i->height <= l->y + l->i->height))
	{
		console_log("hit object\n");
		if (p->y > l->y + l->i->height)
			console_log("hit top\n");
		if (p->x + p->i->width < l->x)
			console_log("hit right\n");
		return (true);
	}
	return (false);
}

bool	hit_object_center(t_player *p, t_listner *l)
{
	const int	x = l->x + l->i->width / 2;
	const int	y = l->y + l->i->height / 2;

	if (p->y + p->i->height >= y
		&& p->y <= y
		&& p->x + p->i->width >= x
		&& p->x <= x)
		return (true);
	return (false);
}

void	hit_map_elements(t_player *p, t_listner *l)
{
	if (l->type == PLAYER)
	{
		p->x = l->x;
		p->y = l->y;
		l->type = START;
	}
	if (l->type == COLLECT && hit_object_center(p, l))
	{
		console_log("hit collect");
		p->wallet++;
		l->i->instances[l->key].enabled = false;
		l->type = EMPTY;
	}
	if (l->type == WALL && hit_object(p, l))
	{
		p->x = l->x;
		p->y = l->y - p->i->height - 3;
		p->jump_height = 0;
		p->state = STAND;
		p->dir = HOLD;
	}
}
