/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/11 23:54:51 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/12 18:27:20 by jensbouma     ########   odam.nl         */
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

# include "../lib/libFT/include/libft.h"
# include "../lib/libmlx42/include/MLX42/MLX42.h"

struct s_file
{
	char	*filetype;
	char	*filename;
};

typedef struct s_textures
{
	struct s_file		*file;
	char				*name;
	struct s_textures	*prev;
	struct s_textures	*next;
}	t_textures;

typedef enum e_filetype
{
	ONLY_TEXTURES,
	MAPS,
	UNKNOWN
}	t_filetype;

mlx_t	*g_mlx;

// defaults.c
void	load_defaults(t_filetype type);


// eroor_handler.c
void	error(char *msg);

// files.c
void	load_map_files(int fd, char *ptr);
void	load_texture_files(int fd, char *ptr);
// void	read_files(char **ptr, void (*func)(int));
void	read_files(char **ptr, void (*func)(int, char *));

// keys.c
void	keyhooks(mlx_key_data_t keydata, void* param);

// player_moves.c
bool	player_ml(void);
bool	player_mu(void);
bool	player_mr(void);
bool	player_md(void);


// array_helpers.c

int		arr_position(int arr[], int key);

#endif