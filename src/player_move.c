/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player_move.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbouma <jbouma@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/30 13:06:41 by jbouma        #+#    #+#                 */
/*   Updated: 2023/05/31 10:39:21 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	player_move_walk(t_game *game, int move)
{
	t_player	*p;

	p = game->player;
	p->state = WALK;
	if (move == LEFT)
		p->x -= (1 * game->scale);
	if (move == RIGHT)
		p->x += (1 * game->scale);
}

void	player_move_jumpfall(t_game *g, int move)
{
	static uint32_t	height = 0;
	t_player		*p;

	p = g->player;
	if (p->state != JUMP && p->state != FALL)
		p->state = JUMP;
	if (p->state == JUMP && p->y - 3 * g->scale > 0 && height < 150 * g->scale)
	{
		p->i = p->t->jump->mlx_i;
		p->y -= 3 * g->scale;
		height += 6 * g->scale;
	}
	else if (p->state == JUMP || p->state == FALL)
	{
		p->state = FALL;
		p->i = p->t->hurt->mlx_i;
		p->y += 2 * g->scale;
		height = 0;
	}
	if (move == LEFT)
		p->x -= (1 * g->scale);
	if (move == RIGHT)
		p->x += (1 * g->scale);
}

void	player_move_jetpack(t_game *game, int move)
{
	t_player	*p;

	p = game->player;
	if (move == LEFT)
		p->x -= (1 * game->scale);
	if (move == RIGHT)
		p->x += (1 * game->scale);
	if (move == UP)
		p->y -= (1 * game->scale);
	if (move == DOWN)
		p->y += (1 * game->scale);
}


void	player_move_duck(t_game *game)
{
	t_player	*p;

	p = game->player;
	p->state = DUCK;
	p->i = p->t->duck->mlx_i;
}

void	player_move_stand(t_game *game)
{
	t_player	*p;

	p = game->player;
	p->state = STAND;
	p->i = p->t->stand->mlx_i;
}