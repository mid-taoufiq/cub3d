/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recast_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakroud <aakroud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:16:02 by aakroud           #+#    #+#             */
/*   Updated: 2025/11/15 11:22:47 by aakroud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_recast_loop_helper(t_win *win, int x)
{
	if (win->distx < win->disty)
	{
		win->distx += win->deltax;
		win->mx += win->sx;
		win->way = 0;
	}
	else
	{
		win->disty += win->deltay;
		win->my += win->sy;
		win->way = 1;
	}
	return ;
}

double	ft_recast_loop(t_win *win, int x)
{
	int		was_hit;

	was_hit = 0;
	while (!was_hit)
	{
		ft_recast_loop_helper(win, x);
		if (win->arr[win->my][win->mx] == '1')
			was_hit = 1;
	}
	if (!win->way)
		return (win->distx - win->deltax);
	else
		return (win->disty - win->deltay);
	return (0.0);
}

void	ft_recast_ray_helper(t_win *win, double ray_dirx, double ray_diry)
{
	if (ray_dirx == 0)
		win->deltax = 999999999999999;
	else
		win->deltax = fabs(1 / ray_dirx);
	if (ray_diry == 0)
		win->deltay = 999999999999999;
	else
		win->deltay = fabs (1 / ray_diry);
}

void	ft_recast_ray(t_win *win, double ray_dirx, double ray_diry)
{
	ft_recast_ray_helper(win, ray_dirx, ray_diry);
	if (ray_dirx < 0)
	{
		win->sx = -1;
		win->distx = (win->start_posx - win->mx) * win->deltax;
	}
	else
	{
		win->sx = 1;
		win->distx = (win->mx + 1 - win->start_posx) * win->deltax;
	}
	if (ray_diry < 0)
	{
		win->sy = -1;
		win->disty = (win->start_posy - win->my) * win->deltay;
	}
	else
	{
		win->sy = 1;
		win->disty = (win->my + 1 - win->start_posy) * win->deltay;
	}
}

void	ft_recast_text(t_win *win, xpm_t **tex,
		double ray_Dirx, double ray_Diry)
{
	if (!win->way && ray_Dirx > 0)
		*tex = win->wall_dim->tex.east;
	else if (!win->way && ray_Dirx < 0)
		*tex = win->wall_dim->tex.west;
	else if (win->way && ray_Diry > 0)
		*tex = win->wall_dim->tex.north;
	else if (win->way && ray_Diry < 0)
		*tex = win->wall_dim->tex.south;
}
