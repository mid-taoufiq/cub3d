/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recasting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakroud <aakroud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:16:57 by aakroud           #+#    #+#             */
/*   Updated: 2025/11/08 11:39:12 by aakroud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	ft_recast_loop(t_win *win, int x)
{
	int		was_hit;

	was_hit = 0;
	while (!was_hit)
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
		if (win->arr[win->my][win->mx] == 'O')
		{
			if (x == (win->width / 2))
			{
				win->door.x = win->mx;
				win->door.y = win->my;
			}
		}
		else if (win->arr[win->my][win->mx] == '1' || win->arr[win->my][win->mx] == 'D')
		{
			was_hit = 1;
			if (win->arr[win->my][win->mx] == 'D')
			{
				win->is_door = 1;
				if (x == (win->width / 2))
				{
					win->door.x = win->mx;
					win->door.y = win->my;
				}
			}
		}
	}
	if (!win->way)
		return (win->distx - win->deltax);
	else
		return (win->disty - win->deltay);
	return (0.0);
}

void	ft_recast_ray(t_win *win, double ray_Dirx, double ray_Diry)
{
	if (ray_Dirx == 0)
		win->deltax = 999999999999999;
	else
		win->deltax = fabs(1 / ray_Dirx);
	if (ray_Diry == 0)
		win->deltay = 999999999999999;
	else
		win->deltay = fabs(1 / ray_Diry);
	if (ray_Dirx < 0)
	{
		win->sx = -1;
		win->distx = (win->start_posx - win->mx) * win->deltax;
	}
	else
	{
		win->sx = 1;
		win->distx = (win->mx + 1 - win->start_posx) * win->deltax;
	}
	if (ray_Diry < 0)
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

void	ft_recast_text(t_win *win, xpm_t **tex, double ray_Dirx, double ray_Diry)
{
	if (win->is_door)
		*tex = win->wall_dim->tex.door;
	else if (!win->way && ray_Dirx > 0)
		*tex = win->wall_dim->tex.east;
	else if (!win->way && ray_Dirx < 0)
		*tex = win->wall_dim->tex.west;
	else if (win->way && ray_Diry > 0)
		*tex = win->wall_dim->tex.north;
	else if (win->way && ray_Diry < 0)
		*tex = win->wall_dim->tex.south;
}

// void	ft_recast_draw()
// {

// }

void	ft_recast_init(t_win *win)
{
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
}

void	ft_recast_helper(t_win *win)
{
	int	x;
	double	camera;
	double	ray_Dirx;
	double	ray_Diry;
	double	wall;
	int	line;
	int ps;
	int pe;
	int draw;
	double wall_x;
	int tex_x;
	xpm_t *tex;
	double	step;
	double	tex_pos;
	int		tex_y;
	uint8_t *pixel;

	x = 0;
	line = 0;
	ps = 0;
	pe = 0;
	draw = 0;
	camera = 0.0;
	ray_Dirx = 0.0;
	ray_Diry = 0.0;
	wall = 0.0;
	step = 0.0;
	ft_recast_init(win);
	while (x < win->width)
	{
		camera = 2 * x / (double)win->width - 1;
		win->mx = (int)win->start_posx;
		win->my = (int)win->start_posy;
		ray_Dirx = win->player_dirx + win->plane_dirx * camera;
		ray_Diry = win->player_diry + win->plane_diry * camera;
		ft_recast_ray(win, ray_Dirx, ray_Diry);
		wall = ft_recast_loop(win, x);
		ft_two_d_map(win, ray_Dirx, ray_Diry, x);
		ft_recast_text(win, &tex, ray_Dirx, ray_Diry);
		if (!win->way)
			wall_x = win->start_posy + wall * ray_Diry;
		else
			wall_x = win->start_posx + wall * ray_Dirx;
		wall_x -= floor(wall_x);
		tex_x = (int)(wall_x * tex->texture.width);
		line = (int)(win->height / wall);
		step = 1.0 * tex->texture.height / line;
		ps = -line / 2 + win->height / 2;
		if (ps < 0)
			ps = 0;
		tex_pos = (ps - win->height / 2 + line / 2) * step;
		pe = line / 2 + win->height / 2;
		if (pe >= win->height)
			pe = win->height - 1;
		draw = 0;
		while (draw < ps)
		{
			mlx_put_pixel(win->img_3d, x, draw, win->wall_dim->ceiling);
			draw += 1;
		}
		while (draw <= pe)
		{
			tex_y = (int)tex_pos % (tex->texture.height - 1);
			tex_pos += step;
			pixel = &tex->texture.pixels[(tex_y * tex->texture.width + tex_x) * 4];
			mlx_put_pixel(win->img_3d, x, draw, ft_color(pixel[0], pixel[1], pixel[2], pixel[3]));
			draw += 1;
		}
		while (draw < win->height)
		{
			mlx_put_pixel(win->img_3d, x, draw, win->wall_dim->floor);
			draw += 1;
		}
		win->is_door = 0;
		x++;
	}
}

void	ft_player_dir_helper(t_win *win, int check)
{
	if (check == 1)
	{
		win->left_vecx = 0;
		win->left_vecy = -1;
		win->right_vecx = 0;
	}
	else if (check == 2)
	{
		win->left_vecx = 0;
		win->left_vecy = 1;
		win->right_vecx = 0;
	}
	else if (check == 3)
	{
		win->left_vecx = 1;
		win->left_vecy = 0;
		win->right_vecx = -1;
	}
	else if (check == 4)
	{
		win->left_vecx = -1;
		win->left_vecy = 0;
		win->right_vecx = 1;
	}
}

void	ft_player_dir(t_win *win, int check)
{
	if (check == 1)
	{
		win->player_dirx = -1;
		win->player_diry = 0;
		win->right_vecy = 1;
	}
	else if (check == 2)
	{
		win->player_dirx = 1;
		win->player_diry = 0;
		win->right_vecy = -1;
	}
	else if (check == 3)
	{
		win->player_dirx = 0;
		win->player_diry = -1;
		win->right_vecy = 0;
	}
	else if (check == 4)
	{
		win->player_dirx = 0;
		win->player_diry = 1;
		win->right_vecy = 0;
	}
	ft_player_dir_helper(win, check);
}

void	ft_recast_check(t_win *win, char c)
{
	if (c == 'W')
	{
		ft_player_dir(win, 1);
		win->plane_dirx = 0;
		win->plane_diry = 0.66;
	}
	else if (c == 'E')
	{
		ft_player_dir(win, 2);
		win->plane_dirx = 0;
		win->plane_diry = -0.66;
	}
	if (c == 'N')
	{
		ft_player_dir(win, 3);
		win->plane_dirx = -0.66;
		win->plane_diry = 0;
	}
	if (c == 'S')
	{
		ft_player_dir(win, 4);
		win->plane_dirx = 0.66;
		win->plane_diry = 0;
	}
}

void	ft_recast(t_win *win, char c, int check)
{
	if (c == 'W')
	{
		if (!check)
			ft_recast_check(win, c);
		ft_recast_helper(win);
	}
	if (c == 'E')
	{
		if (!check)
			ft_recast_check(win, c);
		ft_recast_helper(win);
	}
	if (c == 'N')
	{
		if (!check)
			ft_recast_check(win, c);
		ft_recast_helper(win);
	}
	if (c == 'S')
	{
		if (!check)
			ft_recast_check(win, c);
		ft_recast_helper(win);
	}
	if (win->frames.img != NULL)
		mlx_delete_image(win->mlx, win->frames.img);
	win->frames.img = mlx_texture_to_image(win->mlx, &win->frames.frames[win->frames.current_frame]->texture);
	win->frames.x = win->frames.img->width - 250;
	win->frames.y = win->frames.img->height - 200;
	win->frames.current_frame++;
	if (win->frames.current_frame == win->frames.frames_number)
		win->frames.current_frame = 0;
	if (mlx_image_to_window(win->mlx, win->frames.img, win->frames.x, win->frames.y) == -1)
	{
		mlx_terminate(win->mlx);
		exit (1);
	}
}
