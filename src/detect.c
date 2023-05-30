/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   detect.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/21 15:19:31 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/30 13:40:51 by jbouma        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static bool	detect_range(int x, int s, int e)
{	
	if (x >= s && x <= e)
		return (true);
	return (false);
}

static bool	detect_box(t_player *p, t_hook *h)
{
	const int	r = p->x + p->i->width;
	const int	l = p->x;
	const int	t = p->y;
	const int	b = p->y + p->i->height;
	int			hit;

	hit = 0;
	if (detect_range(r, h->l, h->r) && (detect_range(t, h->t, h->b)
			|| detect_range(b, h->t, h->b)))
		hit += 1;
	if (detect_range(l, h->l, h->r) && (detect_range(t, h->t, h->b)
			|| detect_range(b, h->t, h->b)))
		hit += 1;
	if (detect_range(t, h->t, h->b) && (detect_range(l, h->l, h->r)
			|| detect_range(r, h->l, h->r)))
		hit += 1;
	if (detect_range(b, h->t, h->b) && (detect_range(l, h->l, h->r)
			|| detect_range(r, h->l, h->r)))
		hit += 1;
	if (hit)
		return (true);
	return (false);
}

static bool	detect_center(t_player *p, t_hook *h)
{
	const uint32_t	x = h->l + h->i->width / 2;
	const uint32_t	y = h->t + h->i->height / 2;

	if (p->y + p->i->height >= y
		&& p->y <= y
		&& p->x + p->i->width >= x
		&& p->x <= x)
		return (true);
	return (false);
}

static int	detect_contact(t_player *p, t_hook *h)
{
	if (h->type == PLAYER)
		h->type = START;
	if (h->type == COLLECT && detect_center(p, h))
	{
		p->wallet++;
		h->i->instances[h->key].enabled = false;
		h->type = EMPTY;
	}
	if (h->type == EXIT && detect_box(p, h))
		return (EXIT_OPEN);
	if (h->type == WALL && detect_box(p, h))
	{
		p->block = true;
		if (p->state == JUMP)
			p->state = FALL;
		else
			p->state = STAND;
		return (WALL);
	}
	return (EMPTY);
}

void	detect_hook(void *ptr)
{
	const t_game	*game = (t_game *)ptr;
	t_hook			*h;
	int				trigger;

	h = game->hooks;
	while (h)
	{
		trigger = detect_contact(game->player, h);
		if (trigger == EXIT_OPEN && game->player->wallet >= game->collect)
			exit(EXIT_SUCCESS);
		if (trigger == WALL)
			break ;
		h = h->next;
	}
	if (!game->player->block)
		player_update(ptr);
	else
	{
		game->player->x = game->player->i->instances[0].x;
		game->player->y = game->player->i->instances[0].y;
		game->player->block = false;
	}
	if (game->player->wallet >= game->collect)
		game->exit->i->enabled = true;
}
