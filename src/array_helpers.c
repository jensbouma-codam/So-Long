/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   array_helpers.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/12 14:18:07 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/12 17:16:19 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	arr_position(int arr[], int key)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if ((int)arr[i] == key)
			return (i);
		i++;
	}
	return (-1);
}
