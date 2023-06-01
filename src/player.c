/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 21:49:03 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/06/01 12:18:40 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	player_update(t_game *game)
{
	t_player		*p;
	uint32_t		x;
	uint32_t		y;

	p = game->player;
	x = p->i->instances[0].x;
	y = p->i->instances[0].y;
	if (p->state == WALK)
		p->i = p->t->walk_anim->mlx_i;
	p->t->walk_anim = texture_animate(p->t->walk_anim, p->t->walk);
	if (detect_hook(game))
	{
		p->y = y;
		p->x = x;
	}
	if (p->last_height > p->i->height)
		p->y += p->last_height - p->i->height;
	if (p->last_height < p->i->height)
		p->y -= p->i->height - p->last_height;
	p->i->instances[0].x = p->x;
	p->i->instances[0].y = p->y;
	p->i->instances[0].enabled = true;
	p->block = false;
}

void	player_hook(void *ptr, int move)
{
	const t_game	*g = ptr;
	t_player		*p;

	p = g->player;
	p->last_height = p->i->height;
	p->i->instances[0].enabled = false;
	if (p->jetpack == true)
		player_move_jetpack(ptr, move);
	else if (move == UP || p->state == JUMP || p->state == FALL)
		player_move_jumpfall(ptr, move);
	else if ((move == LEFT || move == RIGHT))
		player_move_walk(ptr, move);
	else if (move == DOWN)
		player_move_duck(ptr);
	else
		player_move_stand(ptr);
	if (!detect_ground(ptr) && p->state == WALK)
		p->state = FALL;
	if (p->jetpack)
		p->t->jetpack->mlx_i->instances->enabled = true;
	else
		p->t->jetpack->mlx_i->instances->enabled = false;
	player_update(ptr);
}

t_player	*player_init(t_game *game)
{
	t_player	*p;

	p = (t_player *)memmory_alloccate(1, sizeof(*p));
	p->t = (t_textures *)memmory_alloccate(1, sizeof(*p->t));
	p->t->stand = player_texture_stand(game);
	p->t->walk = player_texture_walk(game);
	p->t->walk_anim = texture_animate(p->t->walk_anim, p->t->walk);
	p->t->duck = player_texture_duck(game);
	p->t->jump = player_texture_jump(game);
	p->t->hurt = player_texture_hurt(game);
	p->t->jetpack = player_texture_jetpack(game);
	p->y = *game->start_y + 1;
	p->x = *game->start_x + 1;
	p->i = p->t->hurt->mlx_i;
	p->i->instances->enabled = true;
	p->i->instances->y = p->y;
	p->i->instances->x = p->x;
	p->last_height = 0;
	p->state = FALL;
	p->health = 100;
	mlx_loop_hook(game->mlx, &hook_controls, game);
	return (p);
}
