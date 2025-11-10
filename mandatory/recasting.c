/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recasting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakroud <aakroud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:16:57 by aakroud           #+#    #+#             */
/*   Updated: 2025/11/10 18:15:45 by aakroud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	ft_recast_loop_helper(t_win *win, int x, int check)
// {
// 	if (check == 2)
// 	{
// 		if (win->distx < win->disty)
// 		{
// 			win->distx += win->deltax;
// 			win->mx += win->sx;
// 			win->way = 0;
// 		}
// 		else
// 		{
// 			win->disty += win->deltay;
// 			win->my += win->sy;
// 			win->way = 1;
// 		}
// 		return ;
// 	}
// 	if (check == 1)
// 		win->is_door = 1;
// 	if (x == (win->width / 2) && win->door.x == -1 && win->door.y == -1)
// 	{
// 		win->door.x = win->mx;
// 		win->door.y = win->my;
// 	}
// }

// double	ft_recast_loop(t_win *win, int x)
// {
// 	int		was_hit;

// 	was_hit = 0;
// 	while (!was_hit)
// 	{
// 		ft_recast_loop_helper(win, x, 2);
// 		if (win->arr[win->my][win->mx] == 'O')
// 			ft_recast_loop_helper(win, x, 0);
// 		else if (win->arr[win->my][win->mx] == '1'
// 			|| win->arr[win->my][win->mx] == 'D')
// 		{
// 			was_hit = 1;
// 			if (win->arr[win->my][win->mx] == 'D')
// 				ft_recast_loop_helper(win, x, 1);
// 		}
// 	}
// 	if (!win->way)
// 		return (win->distx - win->deltax);
// 	else
// 		return (win->disty - win->deltay);
// 	return (0.0);
// }

// void	ft_recast_ray_helper(t_win *win, double ray_dirx, double ray_diry)
// {
// 	if (ray_dirx == 0)
// 		win->deltax = 999999999999999;
// 	else
// 		win->deltax = fabs(1 / ray_dirx);
// 	if (ray_diry == 0)
// 		win->deltay = 999999999999999;
// 	else
// 		win->deltay = fabs(1 / ray_diry);
// }

// void	ft_recast_ray(t_win *win, double ray_dirx, double ray_diry)
// {
// 	ft_recast_ray_helper(win, ray_dirx, ray_diry);
// 	if (ray_dirx < 0)
// 	{
// 		win->sx = -1;
// 		win->distx = (win->start_posx - win->mx) * win->deltax;
// 	}
// 	else
// 	{
// 		win->sx = 1;
// 		win->distx = (win->mx + 1 - win->start_posx) * win->deltax;
// 	}
// 	if (ray_diry < 0)
// 	{
// 		win->sy = -1;
// 		win->disty = (win->start_posy - win->my) * win->deltay;
// 	}
// 	else
// 	{
// 		win->sy = 1;
// 		win->disty = (win->my + 1 - win->start_posy) * win->deltay;
// 	}
// }

// void	ft_recast_text(t_win *win, xpm_t **tex,
// 		double ray_Dirx, double ray_Diry)
// {
// 	if (win->is_door)
// 		*tex = win->wall_dim->tex.door;
// 	else if (!win->way && ray_Dirx > 0)
// 		*tex = win->wall_dim->tex.east;
// 	else if (!win->way && ray_Dirx < 0)
// 		*tex = win->wall_dim->tex.west;
// 	else if (win->way && ray_Diry > 0)
// 		*tex = win->wall_dim->tex.north;
// 	else if (win->way && ray_Diry < 0)
// 		*tex = win->wall_dim->tex.south;
// }

void	ft_recast_draw(t_win *win, int x)
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

void	ft_recast_init(t_win *win)
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
	win->door.x = -1;
	win->door.y = -1;
	win->is_door = 0;
	win->ps = 0;
	win->pe = 0;
}

void	ft_recast_init_two(t_win *win, int x,
		double *ray_Dirx, double *ray_Diry)
{
	double	camera;

	camera = 2 * x / (double)win->width - 1;
	win->mx = (int)win->start_posx;
	win->my = (int)win->start_posy;
	*ray_Dirx = win->player_dirx + win->plane_dirx * camera;
	*ray_Diry = win->player_diry + win->plane_diry * camera;
}

void	ft_recast_helper_two(t_win *win, double wall,
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
	win->step = (double)win->tex->texture.height / line;
	win->tex_pos = (win->ps - win->height / 2 + line / 2) * win->step;
	win->pe = line / 2 + win->height / 2;
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
		wall = ft_recast_loop(win, x);
		ft_two_d_map(win, ray_dirx, ray_diry, x);
		ft_recast_text(win, &(win->tex), ray_dirx, ray_diry);
		ft_recast_helper_two(win, wall, ray_dirx, ray_diry);
		ft_recast_draw(win, x);
		win->is_door = 0;
		x++;
	}
}
