/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 21:49:03 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/31 10:39:02 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	player_update(t_game *game)
{
	t_player	*p;

	p = game->player;
	if (detect_hook(game)){
		if (p->state == WALK)
		{
			p->t->walk_anim = texture_animate(p->t->walk_anim, p->t->walk);
			p->i = p->t->walk_anim->mlx_i;
		}
		if (p->last_height != p->i->height)
			p->y += p->last_height - p->i->height;
		p->i->instances[0].y = p->y;
		p->i->instances[0].x = p->x;
		p->i->instances[0].enabled = true;
		ft_printf("FPS: %d steps: %d | jumps:%d\r", (uint32_t)(1 / game->mlx->delta_time), p->steps, p->jumps);
	};
}

void	player_hook(void *ptr, int move)
{
	const t_game	*g = ptr;
	t_player		*p;

	p = g->player;
	p->last_height = p->i->height;
	p->i->instances[0].enabled = false;
	if (mlx_is_key_down(((t_game *) ptr)->mlx, MLX_KEY_LEFT_SHIFT))
		player_move_jetpack(ptr, move);
	else if (move == UP || p->state == JUMP || p->state == FALL)
		player_move_jumpfall(ptr, move);
	else if ((move == LEFT || move == RIGHT))
		player_move_walk(ptr, move);
	else if (move == DOWN)
		player_move_duck(ptr);
	else
		player_move_stand(ptr);
	player_update(ptr);
	p->block = false;
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
	p->y = *game->start_y;
	p->x = *game->start_x;
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
