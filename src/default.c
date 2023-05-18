/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   default.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/15 11:10:15 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/18 04:39:32 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

mlx_t	*g_mlx;

t_image	*default_textures(void)
{
	t_image		*i;
	const char	*files[] = {\
		"textures/Base pack/Tiles/box.png",
		NULL};

	i = files_texture_read((char **)files);
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
	p->jump_state = FALL;
	p->action = 0;
	p->stand = default_player_stand();
	p->walk = default_player_walk();
	p->duck = default_player_duck();
	p->jump = default_player_jump();
	p->hurt = default_player_hurt();
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
	game->image = default_textures();
	game->player = default_player();
	return (game);
}
