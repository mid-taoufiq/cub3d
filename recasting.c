#include "cub3d.h"

void	ft_draw(t_win *win, double	wall, int x, int way)
{
	int	line;
	int	ps;
	int	pe;
	int	draw;

	line = 0;
	ps = 0;
	pe = 0;
	draw = 0;
	line = (int)(win->height/wall);
	ps = -line/2 + win->height/2;
	if (ps < 0)
		ps = 0;
	pe = line/2 + win->height/2;
	if (pe >= win->height)
		pe = win->height-1;
	draw = 0;
	while (draw <= ps)
	{
		mlx_put_pixel(win->img_3d, x, draw, ft_color(255, 255, 0, 255));
		draw += 1;
	}
	while (draw <= pe)
	{
		mlx_put_pixel(win->img_3d, x, draw, ft_color(0, 0, 255, 255));
		draw += 1;
	}
	while (draw < win->height)
	{
		mlx_put_pixel(win->img_3d, x, draw, ft_color(255, 255, 0, 255));
		draw += 1;
	}
}

void	ft_recast_helper(t_win *win)
{
	int	x;
	double	camera;
	double	ray_Dirx;
	double	ray_Diry;
	int		mx;
	int		my;
	double	deltax;
	double	deltay;
	double	distance;
	int		sx;
	int		sy;
	int		was_hit;
	int		way;
	double	wall;

	x = 0;
	camera = 0.0;
	ray_Dirx = 0.0;
	ray_Diry = 0.0;
	mx = 0;
	my = 0;
	deltax = 0.0;
	deltay = 0.0;
	sx = 0;
	sy = 0;
	was_hit = 0;
	way = 0;
	wall = 0.0;
	distance = 0.0;
	while (x < win->width)
	{
		camera = 2 * x / (double)win->width - 1;
		mx = (int)win->start_posx;
		my = (int)win->start_posy;
		ray_Dirx = win->player_dirx + win->plane_dirx*camera;
		ray_Diry = win->player_diry + win->plane_diry*camera;
		if (ray_Dirx == 0)
			deltax = 999999999999999;
		else
			deltax = fabs(1/ray_Dirx);
		if (ray_Diry == 0)
			deltay = 999999999999999;
		else
			deltay = fabs(1/ray_Diry);
		if (ray_Dirx < 0)
		{
			sx = -1;
			win->distx = (win->start_posx - mx) * deltax;
		}
		else
		{
			sx = 1;
			win->distx = (mx + 1 - win->start_posx) * deltax;
		}
		if (ray_Diry < 0)
		{
			sy = -1;
			win->disty = (win->start_posy - my) * deltay;
		}
		else
		{
			sy = 1;
			win->disty = (my + 1 - win->start_posy) * deltay;
		}
		was_hit = 0;
		while (!was_hit)
		{
			if (win->distx < win->disty)
			{
				win->distx += deltax;
				mx += sx;
				way = 0;
			}
			else 
			{
				win->disty += deltay;
				my += sy;
				way = 1;
			}
			if (win->arr[my][mx] != '0')
				was_hit = 1;
		}
		if (!way)
			wall = win->distx - deltax;
		else
			wall = win->disty - deltay;
		ft_two_d_map(win, ray_Dirx, ray_Diry, x);
		ft_draw(win, wall, x, way);
		x++;
	}
}

void	ft_player_dir(t_win *win, int check)
{
	if (check == 1)
	{
		win->player_dirx = -1;
		win->player_diry = 0;
	}
	else if (check == 2)
	{
		win->player_dirx = 1;
		win->player_diry = 0;
	}
	else if (check == 3)
	{
		win->player_dirx = 0;
		win->player_diry = -1;
	}
	else if (check == 4)
	{
		win->player_dirx = 0;
		win->player_diry = 1;
	}
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
}
