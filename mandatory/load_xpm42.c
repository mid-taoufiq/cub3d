/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_xpm42.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakroud <aakroud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:05:25 by tibarike          #+#    #+#             */
/*   Updated: 2025/11/15 11:03:06 by aakroud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_textures(t_win *win)
{
	mlx_delete_xpm42(win->wall_dim->tex.east);
	mlx_delete_xpm42(win->wall_dim->tex.north);
	mlx_delete_xpm42(win->wall_dim->tex.west);
	mlx_delete_xpm42(win->wall_dim->tex.south);
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
	return (0);
}
