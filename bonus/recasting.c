#include "cub3d.h"

// void	ft_draw(t_win *win, double	wall, int x, int way)
// {
// 	int	line;
// 	int	ps;
// 	int	pe;
// 	int	draw;

// 	line = 0;
// 	ps = 0;
// 	pe = 0;
// 	draw = 0;
// 	line = (int)(win->height/wall);
// 	ps = -line/2 + win->height/2;
// 	if (ps < 0)
// 		ps = 0;
// 	pe = line/2 + win->height/2;
// 	if (pe >= win->height)
// 		pe = win->height-1;
// 	draw = 0;
// 	while (draw <= ps)
// 	{
// 		mlx_put_pixel(win->img_3d, x, draw, ft_color(255, 255, 0, 255));
// 		draw += 1;
// 	}
// 	while (draw <= pe)
// 	{
// 		mlx_put_pixel(win->img_3d, x, draw, ft_color(0, 0, 255, 255));
// 		draw += 1;
// 	}
// 	while (draw < win->height)
// 	{
// 		mlx_put_pixel(win->img_3d, x, draw, ft_color(255, 255, 0, 255));
// 		draw += 1;
// 	}
// }

// void	ft_recast_helper(t_win *win)
// {
// 	int	x;
// 	double	camera;
// 	double	ray_Dirx;
// 	double	ray_Diry;
// 	int		mx;
// 	int		my;
// 	double	deltax;
// 	double	deltay;
// 	double	distance;
// 	int		sx;
// 	int		sy;
// 	int		was_hit;
// 	int		way;
// 	double	wall;
// 	double wall_x;
// 	int tex_x;
// 	xpm_t *tex;
// 	double	step;
// 	double	tex_pos;
// 	int		tex_y;
// 	uint8_t *pixel;
// 	int	line;
// 	int	ps;
// 	int	pe;
// 	int	draw;

// 	line = 0;
// 	ps = 0;
// 	pe = 0;
// 	draw = 0;

// 	x = 0;
// 	camera = 0.0;
// 	ray_Dirx = 0.0;
// 	ray_Diry = 0.0;
// 	mx = 0;
// 	my = 0;
// 	deltax = 0.0;
// 	deltay = 0.0;
// 	sx = 0;
// 	sy = 0;
// 	was_hit = 0;
// 	way = 0;
// 	wall = 0.0;
// 	distance = 0.0;
// 	while (x < win->width)
// 	{
// 		camera = 2 * x / (double)win->width - 1;
// 		mx = (int)win->start_posx;
// 		my = (int)win->start_posy;
// 		ray_Dirx = win->player_dirx + win->plane_dirx*camera;
// 		ray_Diry = win->player_diry + win->plane_diry*camera;
// 		if (ray_Dirx == 0)
// 			deltax = 999999999999999;
// 		else
// 			deltax = fabs(1/ray_Dirx);
// 		if (ray_Diry == 0)
// 			deltay = 999999999999999;
// 		else
// 			deltay = fabs(1/ray_Diry);
// 		if (ray_Dirx < 0)
// 		{
// 			sx = -1;
// 			win->distx = (win->start_posx - mx) * deltax;
// 		}
// 		else
// 		{
// 			sx = 1;
// 			win->distx = (mx + 1 - win->start_posx) * deltax;
// 		}
// 		if (ray_Diry < 0)
// 		{
// 			sy = -1;
// 			win->disty = (win->start_posy - my) * deltay;
// 		}
// 		else
// 		{
// 			sy = 1;
// 			win->disty = (my + 1 - win->start_posy) * deltay;
// 		}
// 		was_hit = 0;
// 		while (!was_hit)
// 		{
// 			if (win->distx < win->disty)
// 			{
// 				win->distx += deltax;
// 				mx += sx;
// 				way = 0;
// 			}
// 			else 
// 			{
// 				win->disty += deltay;
// 				my += sy;
// 				way = 1;
// 			}
// 			if (win->arr[my][mx] == '1')
// 				was_hit = 1;
// 		}
// 		if (!way)
// 			wall = win->distx - deltax;
// 		else
// 			wall = win->disty - deltay;
// 			if (!way)
// 			wall = win->distx - deltax;
// 		else
// 			wall = win->disty - deltay;
// 		ft_two_d_map(win, ray_Dirx, ray_Diry, x);
// 		if (!way && ray_Dirx > 0)
// 			tex = win->wall_dim->tex.east;
// 		else if (!way && ray_Dirx < 0)
// 			tex = win->wall_dim->tex.west;
// 		else if (way && ray_Diry > 0)
// 			tex = win->wall_dim->tex.north;
// 		else if (way && ray_Diry < 0)
// 			tex = win->wall_dim->tex.south;
// 		if (!way)
// 			wall_x = win->start_posy + wall * ray_Diry;
// 		else
// 			wall_x = win->start_posx + wall * ray_Dirx;
// 		wall_x -= floor(wall_x);
// 		tex_x = (int)(wall_x * tex->texture.width);
// 		if ((way == 0 && ray_Dirx > 0) || (way == 1 && ray_Diry < 0))
// 			tex_x = tex->texture.width - tex_x - 1; 
// 		line = (int)(win->height/wall);
// 		step = 1.0 * tex->texture.height / line;
// 		ps = -line/2 + win->height/2;
// 		tex_pos = (ps - win->height / 2 + line / 2) * step;
// 		if (ps < 0)
// 			ps = 0;
// 		tex_pos = (ps - win->height / 2 + line / 2) * step;
// 		pe = line/2 + win->height/2;
// 		if (pe >= win->height)
// 			pe = win->height-1;
// 		draw = 0;
// 		while (draw < ps)
// 		{
// 			mlx_put_pixel(win->img_3d, x, draw, win->wall_dim->ceiling);
// 			draw += 1;
// 		}
// 		while (draw <= pe)
// 		{
// 			tex_y = (int)tex_pos % (tex->texture.height - 1);
// 			tex_pos += step;
// 			pixel = &tex->texture.pixels[(tex_y * tex->texture.width + tex_x) * 4];
// 			mlx_put_pixel(win->img_3d, x, draw, ft_color(pixel[0], pixel[1], pixel[2], pixel[3]));
// 			draw += 1;
// 		}
// 		while (draw < win->height)
// 		{
// 			mlx_put_pixel(win->img_3d, x, draw, win->wall_dim->floor);
// 			draw += 1;
// 		}
// 		// ft_draw(win, wall, x, way);
// 		x++;
// 	}
// }

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
	int		is_door;

	win->door.x = -1;
	win->door.y = -1;
	x = 0;
	line = 0;
	ps = 0;
	pe = 0;
	draw = 0;
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
	is_door = 0;
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
			if (win->arr[my][mx] == 'O')
			{
				if (x == (win->width / 2) && win->door.x == -1 && win->door.y == -1)
				{
					win->door.x = mx;
					win->door.y = my;
				}
			}
			else if (win->arr[my][mx] == '1' || win->arr[my][mx] == 'D')
			{
				was_hit = 1;
				if (win->arr[my][mx] == 'D')
				{
					is_door = 1;
					if (x == (win->width / 2) && win->door.x == -1 && win->door.y == -1)
					{
						win->door.x = mx;
						win->door.y = my;
					}
				}
			}
		}
		if (!way)
			wall = win->distx - deltax;
		else
			wall = win->disty - deltay;
		ft_two_d_map(win, ray_Dirx, ray_Diry, x);
		if (is_door)
			tex = win->wall_dim->tex.door;
		else if (!way && ray_Dirx > 0)
			tex = win->wall_dim->tex.east;
		else if (!way && ray_Dirx < 0)
			tex = win->wall_dim->tex.west;
		else if (way && ray_Diry > 0)
			tex = win->wall_dim->tex.north;
		else if (way && ray_Diry < 0)
			tex = win->wall_dim->tex.south;
		if (!way)
			wall_x = win->start_posy + wall * ray_Diry;
		else
			wall_x = win->start_posx + wall * ray_Dirx;
		wall_x -= floor(wall_x);
		tex_x = (int)(wall_x * tex->texture.width);
		line = (int)(win->height/wall);
		ps = -line/2 + win->height/2;
		if (ps < 0)
			ps = 0;
		step = (double)tex->texture.height / line;
		tex_pos = (ps - win->height / 2 + line / 2) * step;
		pe = line/2 + win->height/2;
		if (pe >= win->height)
			pe = win->height-1;
		draw = 0;
		while (draw < ps)
		{
			mlx_put_pixel(win->img_3d, x, draw, win->wall_dim->ceiling);
			draw += 1;
		}
		while (draw <= pe)
		{
			tex_y = (int)tex_pos % tex->texture.height;
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
		is_door = 0;
		x++;
	}
}

void	ft_player_dir(t_win *win, int check)
{
	if (check == 1)
	{
		win->player_dirx = -1;
		win->player_diry = 0;
		win->right_vecx = 0;
		win->right_vecy = 1;
		win->left_vecx = 0;
		win->left_vecy = -1;
	}
	else if (check == 2)
	{
		win->player_dirx = 1;
		win->player_diry = 0;
		win->right_vecx = 0;
		win->right_vecy = -1;
		win->left_vecx = 0;
		win->left_vecy = 1;
	}
	else if (check == 3)
	{
		win->player_dirx = 0;
		win->player_diry = -1;
		win->right_vecx = -1;
		win->right_vecy = 0;
		win->left_vecx = 1;
		win->left_vecy = 0;
	}
	else if (check == 4)
	{
		win->player_dirx = 0;
		win->player_diry = 1;
		win->right_vecx = 1;
		win->right_vecy = 0;
		win->left_vecx = -1;
		win->left_vecy = 0;
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

void	handle_frames(t_win *win)
{
	double frame_timer;

	frame_timer = mlx_get_time();
	if (win->frames.img != NULL)
		mlx_delete_image(win->mlx, win->frames.img);
	win->frames.img = mlx_texture_to_image(win->mlx, &win->frames.frames[win->frames.current_frame]->texture);
	if (!win->frames.img)
	{
		mlx_terminate(win->mlx);
		exit (1);
	}
	win->frames.x = win->frames.img->width - 250;
	win->frames.y = win->frames.img->height - 200;
	if (mlx_image_to_window(win->mlx, win->frames.img, win->frames.x, win->frames.y) == -1)
	{
		mlx_terminate(win->mlx);
		exit (1);
	}
	if (frame_timer - win->frames.timer > 0.05)
	{
		win->frames.timer = frame_timer;
		win->frames.current_frame++;
		if (win->frames.current_frame == win->frames.frames_number)
			win->frames.current_frame = 0;
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
	else if (c == 'E')
	{
		if (!check)
			ft_recast_check(win, c);
		ft_recast_helper(win);
	}
	else if (c == 'N')
	{
		if (!check)
			ft_recast_check(win, c);
		ft_recast_helper(win);
	}
	else if (c == 'S')
	{
		if (!check)
			ft_recast_check(win, c);
		ft_recast_helper(win);
	}
	handle_frames(win);
}
