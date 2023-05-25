/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/11 23:54:51 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/26 00:37:22 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# ifndef DEBUG
#  define DEBUG 0
# endif

# ifndef NOMLX
#  define NOMLX 0
# endif

# include <stdbool.h>
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

# include <string.h>
# include <errno.h>
# include <stdio.h>

# include "../lib/libft/include/libft.h"
# include "../lib/libmlx42/include/MLX42/MLX42.h"
# include "../lib/libglfw3/include/GLFW/glfw3.h"

typedef struct s_image
{
	struct s_image	*prev;
	struct s_image	*next;
	char			*name;
	mlx_image_t		*mlx_i;
	bool			first_run;
	int				frame_delay;
}	t_image;

typedef struct s_tiles
{
	struct s_tiles	*prev;
	struct s_tiles	*next;
	char			type;
	bool			reachable;
	uint32_t		x;
	uint32_t		y;
}	t_tiles;

typedef struct s_level
{
	struct s_level	*prev;
	struct s_level	*next;
	struct s_level	*last;
	char			*name;
	t_tiles			*tile;
	t_tiles			*tile_last;
	uint32_t		c_player;
	uint32_t		c_exit;
	uint32_t		c_collectible;
	uint32_t		c_wall;
	uint32_t		c_empty;
	uint32_t		w;
	uint32_t		h;
}	t_level;

typedef struct s_p_image
{
	t_image		*walk;
	t_image		*walk_anim;
	t_image		*stand;
	t_image		*duck;
	t_image		*jump;
	t_image		*hurt;
	t_image		*jetpack;
}	t_p_image;

typedef struct s_player
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	dir;
	uint32_t	health;
	uint32_t	steps;
	uint32_t	jumps;
	bool		jetpack;
	uint32_t	wallet;
	uint32_t	jump_height;
	uint32_t	state;
	uint32_t	trigger;
	bool		block;
	t_p_image	*t;
	mlx_image_t	*i;
}	t_player;

typedef struct s_hooks
{
	struct s_hooks	*prev;
	struct s_hooks	*next;
	char			type;
	uint32_t		t;
	uint32_t		b;
	uint32_t		l;
	uint32_t		r;
	uint32_t		key;
	mlx_image_t		*i;
}	t_hook;

typedef struct s_game
{
	mlx_t		*mlx;
	t_level		*level;
	double		scale;
	t_player	*player;
	t_image		*level_textures;
	t_hook		*hooks;
	uint32_t	*start_x;
	uint32_t	*start_y;
	uint32_t	collect;
	t_hook		*exit;
}	t_game;

typedef enum e_direction
{
	LEFT,
	UP,
	RIGHT,
	DOWN,
	HOLD
}	t_direction;

typedef enum e_player_state
{
	MWA,
	STAND,
	DUCK,
	JUMP,
	FALL,
	HURT,
	WALK,
	JUMP_ACTIVE
}	t_player_state;

typedef enum e_map_elements
{
	EMPTY		= '0',
	WALL		= '1',
	EXIT		= 'E',
	EXIT_OPEN	= 'O',
	COLLECT		= 'C',
	PLAYER		= 'P',
	START		= 'S'
}	t_map_elements;

void			detect_hook(void *game);

char			*file_getname(char *ptr);
void			*file_open(char **ptr, void *(f)(int fd, char *ptr));

t_game			*game_init(int argc, char **argv);

void			hook_loop(void *ptr);
void			hook_controls(void *game);

void			level_check_filename(t_level *level);
void			level_check_elements(t_level *level);
void			level_check_rectangular(t_level *level);
void			level_check_surrounded(t_level *level);
void			level_check_path(t_level *level);

void			level_check(t_level *level);

void			level_draw(t_game *game);

void			*level_read(int fd, char *ptr);
t_level			*level_default(void);
t_image			*level_textures(t_game *game);

t_image			*player_texture_stand(t_game *game);
t_image			*player_texture_walk(t_game *game);
t_image			*player_texture_duck(t_game *game);
t_image			*player_texture_jump(t_game *game);
t_image			*player_texture_hurt(t_game *game);
t_image			*player_texture_jetpack(t_game *g);

void			player_update(t_game *game);
void			player_hook(void *ptr);
t_player		*player_init(t_game *game);

t_image			*texture_animate(t_image *a, t_image *i);
t_image			*texture_read_files(t_game *g, char **ptr, double scale);

void			error(char *msg);
void			debug(const char *s, ...);
void			print(const char *s, ...);
void			*memmory_alloccate(size_t count, size_t size);

#endif