/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/18 23:21:05 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/19 11:59:05 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	in_r(int x, int s, int e)
{	
	if (x >= s && x <= e)
		return (true);
	return (false);
}

bool	hit_object(t_player *p, t_listner *e)
{
	const int	r = p->x + p->i->width;
	const int	l = p->x;
	const int	t = p->y;
	const int	b = p->y + p->i->height;
	int			hit;

	hit = 0;
	e->i->instances[e->key].enabled = 1;
	if (in_r(r, e->l, e->r) && (in_r(t, e->t, e->b) || in_r(b, e->t, e->b)))
		hit += 1;
	if (in_r(l, e->l, e->r) && (in_r(t, e->t, e->b) || in_r(b, e->t, e->b)))
		hit += 1;
	if (in_r(t, e->t, e->b) && (in_r(l, e->l, e->r) || in_r(r, e->l, e->r)))
		hit += 1;
	if (in_r(b, e->t, e->b) && (in_r(l, e->l, e->r) || in_r(r, e->l, e->r)))
		hit += 1;
	if (hit)
	{
		e->i->instances[e->key].enabled = 0;
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
		p->y = p->y + 5;
		p->state = STAND;
		p->dir = HOLD;
	}
}
