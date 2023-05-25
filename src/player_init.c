/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   inti_player.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 21:49:03 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/24 21:49:10 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_player	*init_player(t_game *game)
{
	t_player	*p;

	p = (t_player *)memmory_alloccate(1, sizeof(*p));
	p->t = (t_playeri *)memmory_alloccate(1, sizeof(*p->t));
	p->t->stand = init_player_stand(game);
	p->t->walk = init_player_walk(game);
	p->t->walk_anim = animate(p->t->walk_anim, p->t->walk);
	p->t->duck = init_player_duck(game);
	p->t->jump = init_player_jump(game);
	p->t->hurt = init_player_hurt(game);
	p->i = p->t->walk_anim->mlx_image;
	p->i->instances->enabled = true;
	p->y = *game->start_y;
	p->x = *game->start_x;
	p->jump_height = 0;
	p->health = 100;
	p->wallet = 0;
	p->dir = HOLD;
	p->state = FALL;
	p->trigger = 0;
	mlx_loop_hook(game->mlx, &hook_controls, game);
	mlx_loop_hook(game->mlx, &player_hook, game);
	return (p);
}