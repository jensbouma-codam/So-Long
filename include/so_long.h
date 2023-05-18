/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/11 23:54:51 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/18 23:33:31 by jensbouma     ########   odam.nl         */
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
	struct s_image	*prev;
	struct s_image	*next;
	char			*name;
	struct s_file	*file;
	mlx_image_t		*mlx_image;
}	t_image;

typedef struct s_tile
{
	struct s_tile	*prev;
	struct s_tile	*next;
	char			type;
	int				x;
	int				y;
}	t_tile;

typedef struct s_map
{
	struct s_map	*prev;
	struct s_map	*next;
	char			*name;
	t_tile			*tile;
	t_tile			*last_tile;
	int				width;
	int				height;
}	t_map;

typedef struct s_pt
{
	t_image		*walk;
	t_image		*walk_anim;
	t_image		*stand;
	t_image		*duck;
	t_image		*jump;
	t_image		*hurt;
}	t_pt;

typedef struct s_player
{
	int32_t		x;
	int32_t		y;
	int			dir;
	int			health;
	int			wallet;
	int			jump_height;
	int			state;
	int			trigger;
	double		scale;
	struct s_pt	*t;
	mlx_image_t	*i;
}	t_player;

typedef struct s_game
{
	struct s_map	*map;
	int				*map_type;
	struct s_map	*map_last;
	struct s_player	*player;
	struct s_image	*map_texture;
	bool			move_block;
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

typedef struct s_listner
{
	struct s_listner	*prev;
	struct s_listner	*next;
	char				type;
	int					x;
	int					y;
	int					key;
	mlx_image_t			*i;
}	t_listner;

extern mlx_t		*g_mlx;
extern t_listner	*g_listner;

static void	console_print(const char *s, va_list list);
void		console_error(char *msg);
void		console_debug(const char *s, ...);
void		console_log(const char *s, ...);
void		console_print_map(t_map *map);

t_map		*default_maps(void);
t_image		*default_textures(double scale);
t_player	*default_player(double scale, t_game *game);
t_game		*default_init(int argc, char **argv);

t_image		*default_player_walk(double scale);
t_image		*default_player_stand(double scale);
t_image		*default_player_duck(double scale);
t_image		*default_player_jump(double scale);
t_image		*default_player_hurt(double scale);

t_map		*files_read_map(int fd, char *ptr);
t_map		*files_open_map(char **ptr);
t_image		*files_texture_read(char **ptr, double scale);
char		*files_get_filename(char *ptr);

void		hook_interface_keys(mlx_key_data_t keydata, void *param);
// void		hook_player(t_player *player);

void		hook_player(void *param);
// void		hook_action(void **param);
void		hook_player_keys(void *param);
void		hook_exit(void *parm);
void		hook_listner(void *param);

void		hit_map_elements(t_player *p, t_listner *l);

void		map_draw(t_game **game);
void		map_add(t_map *map, char *line, int y);

void		*memmory_alloccate(size_t count, size_t size);

double		game_window(t_map *map);
void		game_exit(int sig);

void		player_init(t_player *p);
void		player_update(t_player *p);
void		player_jump(t_player *player);
void		player_fall(t_player *player);

#endif