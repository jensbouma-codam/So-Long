/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/15 11:10:15 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/06/01 16:39:35 by jbouma        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	game_loop_hook(void *ptr)
{
	t_game		*game;
	t_player	*p;

	game = ptr;
	p = game->player;
	print("Moves: %d\r", p->steps);
}

static void	game_exit_hook(void *ptr)
{
	const t_game	*game = ptr;

	print("Thanks for playing! Check https:/jensbouma.com \
for my other projects! :)\n");
	mlx_terminate(game->mlx);
	if (DEBUG && system("leaks so_long"))
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

static void	game_key_hook(mlx_key_data_t keydata, void *ptr)
{	
	if ((keydata.key == MLX_KEY_ESCAPE)
		|| (keydata.key == MLX_KEY_C
			&& keydata.modifier == MLX_CONTROL))
		game_exit_hook(ptr);
	return ;
}

static double	game_window(t_game *game)
{
	const t_level	*level = game->level;
	int32_t			display_x;
	int32_t			display_y;
	double			size;
	double			scale;

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
	while ((size * level->w) < display_x && (size * level->h) < display_y)
		size += 1;
	while ((size * level->w) > display_x || (size * level->h) > display_y)
		size -= 1;
	mlx_set_window_size(game->mlx, size * level->w, size * level->h);
	mlx_set_window_pos(game->mlx,
		((display_x + 100) / 2) - (size * level->w) / 2,
		((display_y + 100) / 2) - (size * level->h / 2));
	return (size / scale);
}

/**
 * @brief 
 * 
 * @param argc 
 * @param argv 
 * @return t_game* 
 */
t_game	*game_init(int argc, char **argv)
{
	t_game	*game;

	game = (t_game *)memmory_alloccate(1, sizeof(*game));
	if (argc > 1)
		game->level = file_open(argv + 1, level_read);
	else
		game->level = level_default();
	if (!NOMLX)
	{
		game->mlx = mlx_init(1, 1, "SoLong", false);
		if (!game->mlx)
			error("Failed to initialize graphics");
		game->scale = game_window(game);
		game->level_textures = level_textures(game);
		level_draw(game);
		game->player = player_init(game);
		if ((1 / game->scale) == 0 || (1 * game->scale) == 0)
			game->scale = 1;
		mlx_key_hook(game->mlx, &game_key_hook, game);
		mlx_loop_hook(game->mlx, &game_loop_hook, game);
		mlx_close_hook(game->mlx, &game_exit_hook, game);
	}
	return (game);
}
