/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 11:40:58 by tibarike          #+#    #+#             */
/*   Updated: 2025/10/22 13:44:03 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_extansion(char *line, char *extansion, int option)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	if (!option)
	{
		if (line[i - 1] != extansion[3] || line[i - 2] != extansion[2]
			|| line[i - 3] != extansion[1] || line[i - 4] != extansion[0])
			return (0);
	}
	else
	{
		if (line[i - 1] != extansion[5] || line[i - 2] != extansion[4]
			|| line[i - 3] != extansion[3] || line[i - 4] != extansion[2]
			|| line[i - 5] != extansion[1] || line[i - 6] != extansion[0])
			return (0);
	}
	return (1);
}

int	ft_check_player(char c)
{
	if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
		return (1);
	return (0);
}

int	ft_color(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
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
		if (!way && ray_Dirx > 0)
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
		if ((way == 0 && ray_Dirx > 0) || (way == 1 && ray_Diry < 0))
			tex_x = tex->texture.width - tex_x - 1; 
		line = (int)(win->height/wall);
		step = 1.0 * tex->texture.height / line;
		ps = -line/2 + win->height/2;
		if (ps < 0)
			ps = 0;
		tex_pos = (ps - win->height / 2 + line / 2) * step;
		pe = line/2 + win->height/2;
		if (pe >= win->height)
			pe = win->height-1;
		draw = 0;
		while (draw < ps)
		{
			mlx_put_pixel(win->img, x, draw, win->wall_dim->ceiling);
			draw += 1;
		}
		while (draw <= pe)
		{
			tex_y = (int)tex_pos % (tex->texture.height - 1);
			tex_pos += step;
			pixel = &tex->texture.pixels[(tex_y * tex->texture.width + tex_x) * 4];
			mlx_put_pixel(win->img, x, draw, ft_color(pixel[0], pixel[1], pixel[2], pixel[3]));
			draw += 1;
		}
		while (draw < win->height)
		{
			mlx_put_pixel(win->img, x, draw, win->wall_dim->floor);
			draw += 1;
		}
		x++;
	}
}

void	ft_recast(t_win *win, char c, int check)
{
	double	now;
	double	before;
	int		x;
	double	camera;
	double	ray_Dirx;
	double	ray_Diry;
	int		mx;
	int		my;
	double	distance;
	int		sx;
	int		sy;
	int		was_hit;
	int		way;
	double	wall;

	now = 0;
	was_hit = 0;
	wall = 0;
	way = 0;
	sx = 0;
	sy = 0;
	distance = 0;
	before = 0;
	x = 0;
	camera = 0;
	ray_Dirx = 0;
	ray_Diry = 0;
	mx = (int)win->start_posx;
	my = (int)win->start_posy;
	if (c == 'W')
	{
		if (!check)
		{
			win->player_dirx = -1;
			win->player_diry = 0;
			win->plane_dirx = 0;
			win->plane_diry = 0.66;
		}
		ft_recast_helper(win);
	}
	else if (c == 'E')
	{
		if (!check)
		{
			win->player_dirx = 1;
			win->player_diry = 0;
			win->plane_dirx = 0;
			win->plane_diry = -0.66;
		}
		ft_recast_helper(win);
	}
	if (c == 'N')
	{
		if (!check)
		{
			win->player_dirx = 0;
			win->player_diry = -1;
			win->plane_dirx = -0.66;
			win->plane_diry = 0;
		}
		ft_recast_helper(win);
	}
	if (c == 'S')
	{
		if (!check)
		{
			win->player_dirx = 0;
			win->player_diry = 1;
			win->plane_dirx = 0.66;
			win->plane_diry = 0;
		}
		ft_recast_helper(win);
	}
}

void	ft_movement(t_win *win, int check)
{
	int		x;
	int		y;
	int		i;
	int		j;
	char	c;
	int		one;

	x = 0;
	y = 0;
	i = 0;
	j = 0;
	one = 0;
	win->player_tile = win->tile/4;
	while (win->arr[j])
	{
		i = 0;
		x = 0;
		while (win->arr[j][i])
		{
			if (ft_check_player(win->arr[j][i]))
			{
				c = win->arr[j][i];
				if (!check)
				{
					win->player_x = (x * win->tile + win->tile/2);
					win->player_y = (y * win->tile + win->tile/2);
					win->start_posx = win->player_x/win->tile;
					win->start_posy = win->player_y/win->tile;
					win->past_posx = (int)win->start_posx;
					win->past_posy = (int)win->start_posy;
				}
				if (!one)
					ft_recast(win, c, check);
				one = 1;
			}
			x += 1;
			i++;
		}
		y += 1;
		j++;
	}
}

void	ft_clear_img(t_win *win, mlx_image_t *img)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < win->height)
	{
		x = 0;
		while (x < win->width)
		{
			mlx_put_pixel(img, x, y, ft_color(0,0,0,0));
			x++;
		}
		y++;
	}
}

void	ft_rotation(t_win *win, int check)
{
	double store_x;
	double store_y;
	double store_planex;
	double store_planey;

	store_x = win->player_dirx;
	store_y = win->player_diry;
	store_planex = win->plane_dirx;
	store_planey = win->plane_diry;
	if (check == 1)
	{
		win->player_dirx = store_x * cos(0.1) + store_y * sin(0.1);
		win->player_diry = -store_x * sin(0.1) + store_y * cos(0.1);
		win->plane_dirx = store_planex * cos(0.1) + store_planey * sin(0.1);
		win->plane_diry = -store_planex * sin(0.1) + store_planey * cos(0.1);
		win->start_posx = win->player_x/win->tile;
		win->start_posy = win->player_y/win->tile;
	}
	else if (check == 2)
	{
		win->player_dirx = store_x * cos(0.1) - store_y * sin(0.1);
		win->player_diry = store_x * sin(0.1) + store_y * cos(0.1);
		win->plane_dirx = store_planex * cos(0.1) - store_planey * sin(0.1);
		win->plane_diry = store_planex * sin(0.1) + store_planey * cos(0.1);
		win->start_posx = win->player_x/win->tile;
		win->start_posy = win->player_y/win->tile;
	}
}

void	ft_mov_press(t_win *win, int check)
{
	int	my_max;
	int	my_may;

	my_max = 0;
	my_may = 0;
	if (check == 1)
	{
		my_max = (int)(win->player_x + win->player_dirx * 5)/win->tile;
		my_may = (int)(win->player_y/win->tile);
		if (win->arr[my_may][my_max] != '1')
			win->player_x += win->player_dirx * 5;
		my_may = (int)(win->player_y + win->player_diry * 5)/win->tile;
		if (win->arr[my_may][my_max] != '1')
			win->player_y += win->player_diry * 5;
		win->start_posx = win->player_x/win->tile;
		win->start_posy = win->player_y/win->tile;
		ft_clear_img(win, win->img);
		ft_clear_img(win, win->img_player);
		ft_movement(win, 1);
	}
	else if (check == 2)
	{
		my_max = (int)(win->player_x - win->player_dirx * 5)/win->tile;
		my_may = (int)(win->player_y/win->tile);
		if (win->arr[my_may][my_max] != '1')
			win->player_x -= win->player_dirx * 5;
		my_may = (int)(win->player_y - win->player_diry * 5)/win->tile;
		if (win->arr[my_may][my_max] != '1')
			win->player_y -= win->player_diry * 5;
		win->start_posx = win->player_x/win->tile;
		win->start_posy = win->player_y/win->tile;
		ft_clear_img(win, win->img);
		ft_clear_img(win, win->img_player);
		ft_movement(win, 1);
	}
}

void func(mlx_key_data_t keydata, void *param)
{
	t_win	*win;

	win = (t_win *)param;
	if (keydata.key == MLX_KEY_W)
		ft_mov_press(win, 1);
	else if (keydata.key == MLX_KEY_S)
		ft_mov_press(win, 2);
	if (keydata.key == MLX_KEY_RIGHT)
	{
		ft_clear_img(win, win->img);
		ft_rotation(win, 1);
		ft_movement(win, 1);
	}
	else if (keydata.key == MLX_KEY_LEFT)
	{
		ft_clear_img(win, win->img);
		ft_rotation(win, 2);
		ft_movement(win, 1);
	}
}

int	ft_move_player(char **arr, t_win *win)
{
	mlx_key_hook(win->mlx, func, win);
	return (0);
}

char	*ft_strdupo(char *s1)
{
	int		i;
	char	*dup;

	i = 0;
	dup = NULL;
	while (s1[i] != '\0')
		i++;
	dup = (char *)malloc(i + 1);
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void	ft_draw_line(char c, t_win *win, int i, int j)
{
	int	x;
	int	y;
	int	end;

	y = win->player_y;
	x = win->player_x;
	end = win->player_y;
	if (c == 'N')
	{
		while (j >= 0)
		{
			if (win->arr[i][j] != '1')
			{
				while (y >= end - win->tile/2)
				{
					if (win->player_x >= 0 && y >= 0)
						mlx_put_pixel(win->img_player, win->player_x, y, ft_color(0, 0, 0, 255));
					y--;
				}
				end = y;
			}
			else
				break;
			j--;
		}
	}
	
}

char	**ft_alloc_arr(char **map)
{
	int		i;
	int		j;
	char	**dup;

	i = 0;
	j = 0;
	dup = malloc(sizeof(char *) * 9);
	while (map[i])
	{
		dup[i] = ft_strdupo(map[i]);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

int	main(int argc, char **argv)
{
	t_wall		wall_dim;
	int			fd;
	char		*line;
	t_garbage	*garbage;
	t_win		win;

	win.tile = 64;
	struct_init(&wall_dim);
	line = NULL;
	if (argc != 2 || !check_extansion(argv[1], ".cub", 0))
		return (write(2, "Error\nnot valid arguments\n", 27), 1);
	garbage = NULL;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (perror(argv[1]), 1);
	if (!parsing(line, fd, &wall_dim, &garbage))
		return (close(fd), ft_lstclear(&garbage), 1);
	if (!check_remaining(fd, line, &wall_dim, &garbage))
		return (close(fd), ft_lstclear(&garbage), 1);
	if (!parse_map(&wall_dim, 0))
		return (close(fd), ft_lstclear(&garbage), 1);
	win.arr = wall_dim.map;
	win.width = WIDTH;
	win.height = HEIGHT;
	win.wall_dim = &wall_dim;
	win.mlx = mlx_init(win.width, win.height, "my_mlx", true);
	if (!win.mlx)
		exit (1);
	win.img = mlx_new_image(win.mlx, win.width, win.height);
	if (!win.img)
	{
		mlx_terminate(win.mlx);
		exit (1);
	}
	win.img_player = mlx_new_image(win.mlx, win.width, win.height);
	if (!win.img_player)
	{
		mlx_terminate(win.mlx);
		exit (1);
	}
	wall_dim.tex.east = mlx_load_xpm42(wall_dim.ea);
	wall_dim.tex.north = mlx_load_xpm42(wall_dim.no);
	wall_dim.tex.west = mlx_load_xpm42(wall_dim.we);
	wall_dim.tex.south = mlx_load_xpm42(wall_dim.so);
	if (!wall_dim.tex.east || !wall_dim.tex.north || !wall_dim.tex.west
		|| !wall_dim.tex.south)
		return (1);
	ft_movement(&win, 0);
	ft_move_player(win.arr, &win);
	if (mlx_image_to_window(win.mlx, win.img, 0, 0) == -1)
	{
		mlx_terminate(win.mlx);
		exit (1);
	}
	if (mlx_image_to_window(win.mlx, win.img_player, 0, 0) == -1)
	{
		mlx_terminate(win.mlx);
		exit (1);
	}
	mlx_loop(win.mlx);
	return (0);
}
