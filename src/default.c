/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   default.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/15 11:10:15 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/18 23:18:39 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

mlx_t		*g_mlx;
t_listner	*g_listner;

t_image	*default_textures(double scale)
{
	t_image		*i;
	const char	*files[] = {
		"textures/Base pack/Items/coinGold.png",
		"textures/Base pack/Items/coinGold.png",
		"textures/Base pack/Tiles/door_openMid.png",
		"textures/Base pack/Tiles/door_closedMid.png",
		"textures/Base pack/Tiles/castleCenter.png",
		"textures/Base pack/Tiles/grassCenter.png",
		NULL};

	return (files_texture_read((char **)files, scale));
}

t_player	*default_player(double scale, t_game *g_game)
{
	t_player	*p;

	p = (t_player *)memmory_alloccate(1, sizeof(*p));
	p->x = 0;
	p->y = 0;
	p->dir = HOLD;
	p->health = 100;
	p->wallet = 0;
	p->jump_height = 0;
	p->state = FALL;
	p->trigger = 0;
	p->t = (t_pt *)memmory_alloccate(1, sizeof(*p->t));
	p->t->stand = default_player_stand(scale);
	p->t->walk = default_player_walk(scale);
	p->t->duck = default_player_duck(scale);
	p->t->jump = default_player_jump(scale);
	p->t->hurt = default_player_hurt(scale);
	return (p);
}

t_map	*default_maps(void)
{
	t_map		*map;
	const char	*files[] = {\
		"./maps/valid.ber",
		"./maps/valid2.ber",
		NULL};

	map = files_open_map((char **)files);
	return (map);
}

t_game	*default_init(int argc, char **argv)
{
	t_game	*game;
	double	scale;

	g_mlx = mlx_init(1, 1, "SoLong", false);
	if (!g_mlx)
		console_error("Initializing mlx failed");
	game = (t_game *)memmory_alloccate(1, sizeof(*game));
	if (argc > 1)
		game->map = files_open_map(argv + 1);
	else
	{
		console_log("No arguments given. Loading default maps...\n");
		game->map = default_maps();
	}
	scale = game_window(game->map);
	game->map_texture = default_textures(scale);
	game->player = default_player(scale, game);
	game->player->scale = scale * 0.5;
	signal(SIGINT, &game_exit);
	mlx_key_hook(g_mlx, &hook_interface_keys, g_mlx);
	mlx_close_hook(g_mlx, &hook_exit, g_mlx);
	mlx_loop_hook(g_mlx, &hook_player_keys, game->player);
	mlx_loop_hook(g_mlx, &hook_player, game->player);
	mlx_loop_hook(g_mlx, &hook_listner, game);
	return (game);
}
