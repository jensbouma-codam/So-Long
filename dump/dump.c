/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dump.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jensbouma <jensbouma@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/15 10:58:01 by jensbouma     #+#    #+#                 */
/*   Updated: 2023/05/17 19:28:51 by jensbouma     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

void	keyhooks(mlx_key_data_t keydata, void *param)
{	
	const int	moves[] = {
		'A', MLX_KEY_LEFT,
		'W', MLX_KEY_UP,
		'D', MLX_KEY_RIGHT,
		'S', MLX_KEY_DOWN,
		0};
	const bool	(*move_f[])(void) = {
		player_ml,
		player_mu,
		player_mr,
		player_md
	};

	int			move;

	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(g_mlx);
	move = arr_position((int *)moves, keydata.key);
	if (move != -1)
		move_f[move / 2]();
}