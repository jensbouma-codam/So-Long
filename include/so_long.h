/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/11 23:54:51 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/16 15:39:24 by jbouma        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# ifndef DEBUG
#  define DEBUG 0
# endif

# define WIDTH 512
# define HEIGHT 512

# include <stdbool.h>
# include <limits.h>
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

# include "../lib/libFT/include/libft.h"
# include "../lib/libmlx42/include/MLX42/MLX42.h"
# include "../lib/libglfw3/include/GLFW/glfw3.h"

typedef struct s_file
{
	char	*filetype;
	char	*filename;
}	t_file;

typedef struct s_images
{
	char			*name;
	mlx_image_t		*img;
	struct s_images	*prev;
	struct s_images	*next;
}	t_images;

typedef struct s_element
{
	char				type;
	int					x;
	int					y;
	struct s_element	*prev;
	struct s_element	*next;
}	t_element;

typedef struct s_map
{
	char			*name;
	t_element		*element;
	t_element		*last_element;
	int				width;
	int				height;
	struct s_map	*prev;
	struct s_map	*next;
	struct s_map	*last_map;
}	t_map;

typedef enum e_filetype
{
	ONLY_TEXTURES,
	ALL
}	t_filetype;

typedef struct s_player
{
	int32_t		x;
	int32_t		y;
	int			direction;
	int			health;
	int			wallet;
	int			jump_height;
	int			jump_state;
	int			action;
	mlx_image_t	*stand;
	mlx_image_t	*duck;
	mlx_image_t	*jump;
	mlx_image_t	*hurt;
	mlx_image_t	*walk;
}	t_player;

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
	STAND,
	DUCK,
	JUMP,
	FALL,
	HURT,
	WALK,
	JUMP_ACTIVE
}	t_player_state;

t_images	*g_img;
t_map		*g_map;
t_player	*g_player;
mlx_t		*g_mlx;

// globals.c
void		init_globals(void);

// error_handler.c
void		error(char *msg);
void		debug(const char *s, ...);
void		console(const char *s, ...);
void		*safe_calloc(size_t count, size_t size);

// files.c
void		load_files(int argc, char **argv);
void		load_texture_files(int fd, char *ptr);
void		read_files(char **ptr, void (*func)(int, char *));
char		*get_filename(char *ptr);

// maps.c
void		load_map_files(int fd, char *ptr);

// keys.c
void		key_hook(mlx_key_data_t keydata, void *param);
void		player_hook(void *param);
void		action_hook(void *param);

// player_moves.c
void		update_player(void);
void		player_jump(void);
void		player_fall(void);

// array_helpers.c
int			arr_position(int arr[], int key);

#endif