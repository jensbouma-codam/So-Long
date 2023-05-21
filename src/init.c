/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/15 11:10:15 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/21 22:55:25 by jensbouma     ########   odam.nl         */
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
	printf("Player found at %d, %d\n", *game->start_x, *game->start_y);
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

static t_image	*init_textures(t_game *game)
{
	const char	*files[] = {
		"textures/Base pack/Items/coinGold.png",
		"textures/Base pack/Items/coinGold.png",
		"textures/Base pack/Tiles/door_openMid.png",
		"textures/Base pack/Tiles/door_closedMid.png",
		"textures/Base pack/Tiles/castleCenter.png",
		"textures/Base pack/Tiles/grassCenter.png",
		NULL};

	return (file_readimage(game, (char **)files, 1));
}

t_map	*init_defaultmaps(void)
{
	t_map		*map;
	const char	*files[] = {\
		"./maps/valid.ber",
		"./maps/valid2.ber",
		NULL};

	console_log("No arguments given. Loading default maps...\n");
	map = file_open((char **)files, file_readmap);
	return (map);
}

static double	init_window(t_game *game)
{
	const t_map	*map = game->map;
	int32_t		display_x;
	int32_t		display_y;
	double		size;
	double		scale;

	size = 70;
	scale = size;
	mlx_get_monitor_size(0, &display_x, &display_y);
	if (!display_x || !display_y)
	{
		display_x = 1920;
		display_y = 1080;
	}
	display_x -= 100;
	display_y -= 100;
	while ((size * map->width) < display_x && (size * map->height) < display_y)
		size += 1;
	while ((size * map->width) > display_x || (size * map->height) > display_y)
		size -= 1;
	mlx_set_window_size(game->mlx, size * map->width, size * map->height);
	mlx_set_window_pos(game->mlx,
		((display_x + 100) / 2) - (size * map->width) / 2,
		((display_y + 100) / 2) - (size * map->height / 2));
	return (size / scale);
}

/**
 * @brief 
 * 
 * @param argc 
 * @param argv 
 * @return t_game* 
 */
t_game	*init_game(int argc, char **argv)
{
	t_game	*game;

	game = (t_game *)memmory_alloccate(1, sizeof(*game));
	game->mlx = mlx_init(1, 1, "SoLong", false);
	if (!game->mlx)
		console_error_exit("Initializing mlx failed");
	if (argc > 1)
		game->map = file_open(argv + 1, file_readmap);
	else
		game->map = init_defaultmaps();
	game->scale = init_window(game);
	game->textures = init_textures(game);
	map_draw_tiles(game);
	game->player = init_player(game);
	mlx_key_hook(game->mlx, &hook_interface, game);
	mlx_close_hook(game->mlx, &hook_exit, game);
	return (game);
}
