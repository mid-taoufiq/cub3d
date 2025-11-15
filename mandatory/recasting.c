/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recasting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:16:57 by aakroud           #+#    #+#             */
/*   Updated: 2025/11/15 15:15:49 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_recast_draw(t_win *win, int x)
{
	int	draw;

	draw = 0;
	while (draw < win->ps)
	{
		mlx_put_pixel(win->img_3d, x, draw, win->wall_dim->ceiling);
		draw += 1;
	}
	while (draw <= win->pe)
	{
		win->tex_y = (int)win->tex_pos % win->tex->texture.height;
		win->tex_pos += win->step;
		win->pixel = &(win->tex->texture.pixels[(win->tex_y
					* win->tex->texture.width + win->tex_x) * 4]);
		mlx_put_pixel(win->img_3d, x, draw,
			ft_color(win->pixel[0],
				win->pixel[1], win->pixel[2], win->pixel[3]));
		draw += 1;
	}
	while (draw < win->height)
	{
		mlx_put_pixel(win->img_3d, x, draw, win->wall_dim->floor);
		draw += 1;
	}
}

static void	ft_recast_init(t_win *win)
{
	win->step = 0.0;
	win->wall_x = 0.0;
	win->tex_x = 0;
	win->tex = NULL;
	win->step = 0.0;
	win->tex_pos = 0.0;
	win->tex_y = 0;
	win->pixel = NULL;
	win->mx = 0;
	win->my = 0;
	win->deltax = 0.0;
	win->deltay = 0.0;
	win->sx = 0;
	win->sy = 0;
	win->way = 0;
	win->ps = 0;
	win->pe = 0;
}

static void	ft_recast_init_two(t_win *win, int x,
		double *ray_Dirx, double *ray_Diry)
{
	double	camera;

	camera = 2 * x / (double)win->width - 1;
	win->mx = (int)win->start_posx;
	win->my = (int)win->start_posy;
	*ray_Dirx = win->player_dirx + win->plane_dirx * camera;
	*ray_Diry = win->player_diry + win->plane_diry * camera;
}

static void	ft_recast_helper_two(t_win *win, double wall,
		double ray_Dirx, double ray_Diry)
{
	int	line;

	line = 0;
	if (!win->way)
		win->wall_x = win->start_posy + wall * ray_Diry;
	else
		win->wall_x = win->start_posx + wall * ray_Dirx;
	win->wall_x -= floor(win->wall_x);
	win->tex_x = (int)(win->wall_x * win->tex->texture.width);
	line = (int)(win->height / wall);
	win->ps = -line / 2 + win->height / 2;
	if (win->ps < 0)
		win->ps = 0;
	win->pe = line / 2 + win->height / 2;
	win->step = (double)win->tex->texture.height / line;
	win->tex_pos = (win->ps - win->pe) * win->step;
	if (win->pe >= win->height)
		win->pe = win->height - 1;
}

void	ft_recast_helper(t_win *win)
{
	int		x;
	double	ray_dirx;
	double	ray_diry;
	double	wall;

	x = 0;
	ray_dirx = 0.0;
	ray_diry = 0.0;
	wall = 0.0;
	ft_recast_init(win);
	while (x < win->width)
	{
		ft_recast_init_two(win, x, &ray_dirx, &ray_diry);
		ft_recast_ray(win, ray_dirx, ray_diry);
		wall = ft_recast_loop(win);
		ft_recast_text(win, &(win->tex), ray_dirx, ray_diry);
		ft_recast_helper_two(win, wall, ray_dirx, ray_diry);
		ft_recast_draw(win, x);
		x++;
	}
}
