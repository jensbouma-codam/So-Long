/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/11 23:54:51 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/21 18:36:58 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# ifndef DEBUG
#  define DEBUG 0
# endif

# include <stdbool.h>
# include <limits.h>
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <signal.h>

# include "../lib/libft/include/libft.h"
# include "../lib/libmlx42/include/MLX42/MLX42.h"
# include "../lib/libglfw3/include/GLFW/glfw3.h"

typedef struct s_file
{
	char	*filetype;
	char	*filename;
}	t_file;

typedef struct s_image
{
	struct s_image		*prev;
	struct s_image		*next;
	char				*name;
	t_file				*file;
	mlx_image_t			*mlx_image;
	bool				firstrun;
	int					frame_delay;
}	t_image;

typedef struct s_tiles
{
	struct s_tiles	*prev;
	struct s_tiles	*next;
	char			type;
	uint32_t		x;
	uint32_t		y;
}	t_tiles;

typedef struct s_map
{
	struct s_map	*prev;
	struct s_map	*next;
	char			*name;
	t_tiles			*tiles;
	t_tiles			*tiles_last;
	int32_t			width;
	int32_t			height;
}	t_map;

typedef struct s_playeri
{
	t_image		*walk;
	t_image		*walk_anim;
	t_image		*stand;
	t_image		*duck;
	t_image		*jump;
	t_image		*hurt;
}	t_playeri;

typedef struct s_player
{
	uint32_t	x;
	uint32_t	y;
	int32_t		dir;
	int32_t		health;
	int32_t		wallet;
	int32_t		jump_height;
	int32_t		state;
	int32_t		trigger;
	t_playeri	*t;
	mlx_image_t	*i;
}	t_player;

typedef struct s_hooks
{
	struct s_hooks	*prev;
	struct s_hooks	*next;
	char			type;
	uint32_t		x;
	uint32_t		y;
	uint32_t		t;
	uint32_t		b;
	uint32_t		l;
	uint32_t		r;
	int32_t			key;
	mlx_image_t		*i;
}	t_hooks;

typedef struct s_game
{
	mlx_t		*mlx;
	t_map		*map;
	double		scale;
	t_player	*player;
	t_image		*textures;
	t_hooks		*hooks;
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

t_game		*init_game(int argc, char **argv);
t_map		*init_defaultmaps(void);

void		*file_open(char **ptr, void *(f)(int fd, char *ptr));
char		*file_getname(char *ptr);
void		*file_readmap(int fd, char *ptr);
t_image		*file_readimage(t_game *g, char **ptr, double scale);

void		map_draw_tiles(t_game *game);
void		map_add(t_map *map, char *line, int y);

t_image		*init_player_stand(t_game *game);
t_image		*init_player_walk(t_game *game);
t_image		*init_player_duck(t_game *game);
t_image		*init_player_jump(t_game *game);
t_image		*init_player_hurt(t_game *game);

t_image		*animate(t_image *a, t_image *i);

void		hook_exit(t_game *game);
void		hook_interface(mlx_key_data_t keydata, t_game *game);
void		hook_controls(t_game *game);

void		detection_hook(t_game (*game));

t_image		*animate(t_image *a, t_image *i);

void		player_update(t_game *game);
void		player_hook(t_game *game);

void		*memmory_alloccate(size_t count, size_t size);

void		console_error_exit(char *msg);
void		console_error(const char *s, ...);
void		console_debug(const char *s, ...);
void		console_log(const char *s, ...);
void		console_print_map(t_map *map);

#endif