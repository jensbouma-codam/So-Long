/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   detection.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/21 15:19:31 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/21 15:28:28 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static bool	range(int x, int s, int e)
{	
	if (x >= s && x <= e)
		return (true);
	return (false);
}

static bool	detect_box(t_player *p, t_hooks *h)
{
	const int	r = p->x + p->i->width;
	const int	l = p->x;
	const int	t = p->y;
	const int	b = p->y + p->i->height;
	int			hit;

	hit = 0;
	h->i->instances[h->key].enabled = 1;
	if (range(r, h->l, h->r) && (range(t, h->t, h->b) || range(b, h->t, h->b)))
		hit += 1;
	if (range(l, h->l, h->r) && (range(t, h->t, h->b) || range(b, h->t, h->b)))
		hit += 1;
	if (range(t, h->t, h->b) && (range(l, h->l, h->r) || range(r, h->l, h->r)))
		hit += 1;
	if (range(b, h->t, h->b) && (range(l, h->l, h->r) || range(r, h->l, h->r)))
		hit += 1;
	if (hit)
	{
		h->i->instances[h->key].enabled = 0;
		return (true);
	}
	return (false);
}

static bool	detect_center(t_player *p, t_hooks *h)
{
	const int	x = h->x + h->i->width / 2;
	const int	y = h->y + h->i->height / 2;

	if (p->y + p->i->height >= y
		&& p->y <= y
		&& p->x + p->i->width >= x
		&& p->x <= x)
		return (true);
	return (false);
}

static void	detect_contact(t_player *p, t_hooks *h)
{
	if (h->type == PLAYER)
	{
		p->x = h->x;
		p->y = h->y;
		h->type = START;
	}
	if (h->type == COLLECT && detect_center(p, h))
	{
		console_log("hit collect");
		p->wallet++;
		h->i->instances[h->key].enabled = false;
		h->type = EMPTY;
	}
	if (h->type == WALL && detect_box(p, h))
	{
		p->y = p->y + 5;
		p->state = STAND;
		p->dir = HOLD;
	}
}

void	detection_hook(void *param)
{
	t_player	*p;
	t_game		*game;
	t_hooks		*h;

	game = (t_game *)param;
	p = game->player;
	h = game->hooks;
	while (h)
	{
		detect_contact(p, h);
		h = h->next;
	}
	player_update(param);
}
