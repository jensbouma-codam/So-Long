/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   default.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/15 11:10:15 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/18 14:35:22 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

mlx_t	*g_mlx;

t_image	*default_textures(void)
{
	t_image		*i;
	const char	*files[] = {
		"textures/Base pack/Tiles/grassCenter.png",
		"textures/Base pack/Tiles/castleCenter.png",
		"textures/Base pack/Tiles/door_closedMid.png",
		"textures/Base pack/Tiles/door_openMid.png",
		"textures/Base pack/Items/coinGold.png",
		NULL};

	i = files_texture_read((char **)files);
	console_log("NO 3 = %s", i[3].name);
	return (i);
}

t_player	*default_player(void)
{
	t_player	*p;

	p = (t_player *)memmory_alloccate(1, sizeof(*p));
	p->x = 50;
	p->y = 100;
	p->dir = HOLD;
	p->health = 100;
	p->wallet = 0;
	p->jump_height = 0;
	p->state = FALL;
	p->trigger = 0;
	p->t = (t_pt *)memmory_alloccate(1, sizeof(*p->t));
	p->t->stand = default_player_stand();
	p->t->walk = default_player_walk();
	p->t->duck = default_player_duck();
	p->t->jump = default_player_jump();
	p->t->hurt = default_player_hurt();
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

	g_mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
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
	game->map_texture = default_textures();
	game->player = default_player();
	signal(SIGINT, &game_exit);
	mlx_key_hook(g_mlx, &hook_interface_keys, g_mlx);
	mlx_close_hook(g_mlx, &hook_exit, g_mlx);
	mlx_loop_hook(g_mlx, &hook_player_keys, game->player);
	mlx_loop_hook(g_mlx, &hook_player, game->player);
	return (game);
}
