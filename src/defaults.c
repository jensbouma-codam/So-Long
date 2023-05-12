/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   defaults.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/12 13:55:45 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/12 18:10:19 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_defaults(t_filetype type)
{
	const char	*maps[] = {\
		"./maps/test1",
		"./maps/test2",
		NULL};
	const char	*textures[] = {\
		"./textures/test2.txt",
		NULL};

	if (type != ONLY_TEXTURES)
		read_files((char **)maps, load_map_files);
	read_files((char **)textures, load_texture_files);
}