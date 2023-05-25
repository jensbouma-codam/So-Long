/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/21 14:36:10 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/25 12:08:04 by jbouma        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_image	*texture_animate(t_image *a, t_image *i)
{
	if (i->first_run)
		return ((i->first_run = false), i);
	if (i->frame_delay == 0)
	{
		i->frame_delay = 10;
		if (a->next)
			a = a->next;
		else
			a = i;
	}
	else
		i->frame_delay--;
	return (a);
}

static	mlx_image_t	*texture_read_resize(mlx_t *mlx, char *file, double s)
{
	mlx_texture_t	*t;
	mlx_image_t		*i;

	t = mlx_load_png(file);
	if (!t)
		error(ft_strjoin("Failed to load texture: ", file));
	i = mlx_texture_to_image(mlx, t);
	mlx_delete_texture(t);
	if (!i)
		error(ft_strjoin("Failed to convert texture: ", file));
	if (s != 1)
		mlx_resize_image(i, i->width * s, i->height * s);
	return (i);
}

t_image	*texture_read_files(t_game *g, char **ptr, double scale)
{
	t_image			*list;
	t_image			*node;

	list = NULL;
	while (*ptr)
	{
		node = (t_image *)memmory_alloccate(1, sizeof(*node));
		debug("Load texture file: %s\n", *ptr);
		node->mlx_i = texture_read_resize(g->mlx, *ptr, scale * g->scale);
		if (!node->mlx_i)
			error(ft_strjoin("Failed to load texture: ", *ptr));
		mlx_image_to_window(g->mlx, node->mlx_i, 0, 0);
		node->mlx_i->instances->enabled = false;
		node->name = file_getname(*ptr);
		node->next = NULL;
		node->first_run = true;
		node->frame_delay = 0;
		if (list)
			node->next = list;
		list = node;
		ptr++;
	}
	return (list);
}
