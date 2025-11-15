/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakroud <aakroud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:16:49 by aakroud           #+#    #+#             */
/*   Updated: 2025/11/15 10:58:20 by aakroud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	func(void *param)
{
	t_win	*win;

	win = (t_win *)param;
	if (mlx_is_key_down(win->mlx, MLX_KEY_W))
		ft_mov_press(win, 1);
	if (mlx_is_key_down(win->mlx, MLX_KEY_S))
		ft_mov_press(win, 2);
	if (mlx_is_key_down(win->mlx, MLX_KEY_A))
		ft_mov_press(win, 3);
	if (mlx_is_key_down(win->mlx, MLX_KEY_D))
		ft_mov_press(win, 4);
	if (mlx_is_key_down(win->mlx, MLX_KEY_RIGHT))
		ft_rotation(win, 1, 0.04);
	else if (mlx_is_key_down(win->mlx, MLX_KEY_LEFT))
		ft_rotation(win, 2, 0.04);
	if (mlx_is_key_down(win->mlx, MLX_KEY_ESCAPE))
		return (mlx_close_window(win->mlx));
	ft_movement(win, 1);
}

int	ft_move_player(char **arr, t_win *win)
{
	mlx_loop_hook(win->mlx, func, win);
	return (0);
}
