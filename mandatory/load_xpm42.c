/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_xpm42.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:05:25 by tibarike          #+#    #+#             */
/*   Updated: 2025/11/13 13:32:28 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_textures(t_win *win)
{
	mlx_delete_xpm42(win->wall_dim->tex.east);
	mlx_delete_xpm42(win->wall_dim->tex.north);
	mlx_delete_xpm42(win->wall_dim->tex.west);
	mlx_delete_xpm42(win->wall_dim->tex.south);
	mlx_delete_xpm42(win->wall_dim->tex.door);
}

void	free_frames(t_win *win)
{
	mlx_delete_xpm42(win->frames.frames[0]);
	mlx_delete_xpm42(win->frames.frames[1]);
	mlx_delete_xpm42(win->frames.frames[2]);
	mlx_delete_xpm42(win->frames.frames[3]);
	mlx_delete_xpm42(win->frames.frames[4]);
	mlx_delete_xpm42(win->frames.frames[5]);
}

int	init_frames2(t_win *win)
{
	win->frames.frames[4] = mlx_load_xpm42("./textures/frame_4.xpm42");
	if (!win->frames.frames[4])
		return (mlx_delete_xpm42(win->frames.frames[0]),
			mlx_delete_xpm42(win->frames.frames[1]),
			mlx_delete_xpm42(win->frames.frames[2]),
			mlx_delete_xpm42(win->frames.frames[3]), 1);
	win->frames.frames[5] = mlx_load_xpm42("./textures/frame_5.xpm42");
	if (!win->frames.frames[5])
		return (mlx_delete_xpm42(win->frames.frames[0]),
			mlx_delete_xpm42(win->frames.frames[1]),
			mlx_delete_xpm42(win->frames.frames[2]),
			mlx_delete_xpm42(win->frames.frames[3]),
			mlx_delete_xpm42(win->frames.frames[4]), 1);
	win->frames.current_frame = 0;
	win->frames.frames_number = 6;
	win->frames.timer = mlx_get_time();
	return (0);
}

int	init_frames(t_win *win)
{
	win->frames.frames[0] = mlx_load_xpm42("./textures/frame_0.xpm42");
	if (!win->frames.frames[0])
		return (1);
	win->frames.frames[1] = mlx_load_xpm42("./textures/frame_1.xpm42");
	if (!win->frames.frames[1])
		return (mlx_delete_xpm42(win->frames.frames[0]), 1);
	win->frames.frames[2] = mlx_load_xpm42("./textures/frame_2.xpm42");
	if (!win->frames.frames[2])
		return (mlx_delete_xpm42(win->frames.frames[0]),
			mlx_delete_xpm42(win->frames.frames[1]), 1);
	win->frames.frames[3] = mlx_load_xpm42("./textures/frame_3.xpm42");
	if (!win->frames.frames[3])
		return (mlx_delete_xpm42(win->frames.frames[0]),
			mlx_delete_xpm42(win->frames.frames[1]),
			mlx_delete_xpm42(win->frames.frames[2]), 1);
	return (init_frames2(win));
}

int	init_walltex(t_win *win)
{
	win->wall_dim->tex.east = mlx_load_xpm42(win->wall_dim->ea);
	if (!win->wall_dim->tex.east)
		return (1);
	win->wall_dim->tex.north = mlx_load_xpm42(win->wall_dim->no);
	if (!win->wall_dim->tex.north)
		return (mlx_delete_xpm42(win->wall_dim->tex.east), 1);
	win->wall_dim->tex.west = mlx_load_xpm42(win->wall_dim->we);
	if (!win->wall_dim->tex.west)
		return (mlx_delete_xpm42(win->wall_dim->tex.east),
			mlx_delete_xpm42(win->wall_dim->tex.north), 1);
	win->wall_dim->tex.south = mlx_load_xpm42(win->wall_dim->so);
	if (!win->wall_dim->tex.south)
		return (mlx_delete_xpm42(win->wall_dim->tex.east),
			mlx_delete_xpm42(win->wall_dim->tex.north),
			mlx_delete_xpm42(win->wall_dim->tex.west), 1);
	win->wall_dim->tex.door = mlx_load_xpm42(win->wall_dim->d);
	if (!win->wall_dim->tex.door)
		return (mlx_delete_xpm42(win->wall_dim->tex.east),
			mlx_delete_xpm42(win->wall_dim->tex.north),
			mlx_delete_xpm42(win->wall_dim->tex.west),
			mlx_delete_xpm42(win->wall_dim->tex.south), 1);
	return (0);
}
