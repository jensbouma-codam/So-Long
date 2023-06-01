/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 21:49:03 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/06/01 16:12:08 by jbouma        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	player_update_jetpack(t_player *p)
{
	p->state = FALL;
	p->t->jetpack->mlx_i->instances->enabled = true;
	p->t->jetpack->mlx_i->instances->x = (p->x + p->i->width / 2)
		- (p->t->jetpack->mlx_i->width / 2);
	p->t->jetpack->mlx_i->instances->y = p->y + p->i->height
		- p->t->jetpack->mlx_i->height;
}

void	player_update(t_game *game)
{
	t_player		*p;

	p = game->player;
	if (p->state == WALK)
		p->i = p->t->walk_anim->mlx_i;
	p->t->walk_anim = texture_animate(p->t->walk_anim, p->t->walk);
	if (detect_hook(game))
	{
		if (p->state == JUMP)
			p->state = FALL;
		else if (p->state == FALL)
			player_move_stand(game);
		p->y = p->last_y;
		p->x = p->last_x;
	}
	if (p->last_height > p->i->height)
		p->y += p->last_height - p->i->height;
	if (p->last_height < p->i->height)
		p->y -= p->i->height - p->last_height;
	p->i->instances[0].x = p->x;
	p->i->instances[0].y = p->y;
	p->i->instances[0].enabled = true;
	if (p->jetpack == true)
		player_update_jetpack(p);
}

void	player_hook(void *ptr, int move)
{
	const t_game	*g = ptr;
	t_player		*p;

	p = g->player;
	p->last_height = p->i->height;
	p->last_x = p->i->instances[0].x;
	p->last_y = p->i->instances[0].y;
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
	if (!p->jetpack)
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
	p->i = p->t->stand->mlx_i;
	p->y = game->start_y;
	p->x = game->start_x;
	p->i->instances->y = p->y;
	p->i->instances->x = p->x;
	p->i->instances->enabled = true;
	p->last_height = 0;
	p->last_y = p->y;
	p->last_x = p->x;
	p->state = FALL;
	p->health = 100;
	mlx_loop_hook(game->mlx, &hook_controls, game);
	return (p);
}
