/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 11:40:58 by tibarike          #+#    #+#             */
/*   Updated: 2025/11/06 15:01:01 by tibarike         ###   ########.fr       */
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

void	ft_recto(int x, int y, int color, t_win win)
{
	int	start_x;
	int	start_y;

	start_x = x;
	start_y = y;
	while (y < start_y + win.tile - 1)
	{
		x = start_x;
		while (x < start_x + win.tile - 1)
		{
			mlx_put_pixel(win.img, x, y, color);
			x++;
		}
		y++;
	}
}

void	ft_recto_player(int x, int y, int color, t_win win)
{
	int	start_x;
	int	start_y;

	start_x = x;
	start_y = y;
	while (y < start_y + win.tile/4 - 1)
	{
		x = start_x;
		while (x < start_x + win.tile/4 - 1)
		{
			if (x >= 0 && y >= 0)
				mlx_put_pixel(win.img_player, x, y, color);
			x++;
		}
		y++;
	}
}

void	ft_player(int x, int y, int color, t_win win)
{
	int	start_x;
	int	start_y;

	start_x = x;
	start_y = y;
	while (y < start_y + win.tile/3)
	{
		x = start_x;
		while (x < start_x + win.tile/3)
		{
			mlx_put_pixel(win.img, x, y, color);
			x++;
		}
		y++;
	}
	
}

void	ft_put_img(char **arr, t_win *win, int check)
{
	int	x;
	int	y;
	int	i;
	int	j;
	// int	player_tile;

	x = 0;
	y = 0;
	i = 0;
	j = 0;
	// player_tile = win->tile/4;
	if (!arr || !*arr)
		return ;
	while (arr[j])
	{
		i = 0;
		x = 0;
		while (arr[j][i])
		{
			if (arr[j][i] == '1')
				ft_recto(x * win->tile, y * win->tile, ft_color(0, 0, 255, 255), *win);
			else
				ft_recto(x * win->tile, y * win->tile, ft_color(255, 255, 0, 255), *win);
			x += 1;
			i++;
		}
		y += 1;
		j++;
	}
}

void	ft_two_d_map(t_win *win, double ray_Dirx, double ray_Diry)
{
	int my_may;
	int my_max;
	double draw_x;
	double draw_y;
	int		initial1;
	int		initial2;
	int test;
	double new_rayx = 0.0;
	double new_rayy = 0.0;
	draw_x = win->player_x;
	draw_y = win->player_y;
	initial1 = win->player_x;
	initial2 = win->player_y;
	test = 0;
	my_max = (int)draw_x/64;
	my_may = (int)draw_y/64;
	while (win->arr[my_may][my_max] != '1')
	{
		draw_x = initial1 + ray_Dirx * test;
		draw_y = initial2 + ray_Diry * test;
		new_rayx = ray_Dirx * test;
		new_rayy = ray_Diry * test;
		my_max = (int)draw_x/64;
		my_may = (int)draw_y/64;
		if (draw_x < 0 || draw_y < 0)
			break;
		mlx_put_pixel(win->img_player, draw_x, draw_y, ft_color(0,0,0,255));
		test += 1;
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
	win->door.x = -1;
	win->door.y = -1;
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
			if (win->arr[my][mx] == 'O' && x == (win->width / 2))
			{
				win->door.x = mx;
				win->door.y = my;
			}
			else if (win->arr[my][mx] == '1' || win->arr[my][mx] == 'D')
			{
				was_hit = 1;
				if (win->arr[my][mx] == 'D')
				{
					is_door = 1;
					if (x == (win->width / 2))
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
		is_door = 0;
		x++;
	}
}

void	ft_recast(t_win *win, int check)
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
	if (win->wall_dim->player_direction == 'W')
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
	else if (win->wall_dim->player_direction == 'E')
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
	if (win->wall_dim->player_direction == 'N')
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
	if (win->wall_dim->player_direction == 'S')
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

void	ft_movement(t_win *win, int check)
{
	int		x;
	int		y;
	int		i;
	int		j;
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
					ft_recast(win, check);
				one = 1;
			}
			x += 1;
			i++;
		}
		y += 1;
		j++;
	}
}

void	handle_doors(t_win *win)
{
	int	px;
	int	py;

	px = (int)win->start_posx;
	py = (int)win->start_posy;
	if (win->door.x != -1 && win->door.y != -1)
	{
		if (win->arr[win->door.y][win->door.x] == 'D')
		{
			if ((abs(px - win->door.x) <= 1 && win->door.y == py)
				|| (abs(py - win->door.y) <= 1 && win->door.x == px))
				win->arr[win->door.y][win->door.x] = 'O';
		}
		else if (win->arr[win->door.y][win->door.x] == 'O')
		{
			if ((abs(px - win->door.x) <= 1 && win->door.y == py)
				|| (abs(py - win->door.y) <= 1 && win->door.x == px))
				win->arr[win->door.y][win->door.x] = 'D';
		}
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
		win->player_dirx = store_x * cos(0.04) + store_y * sin(0.04);
		win->player_diry = -store_x * sin(0.04) + store_y * cos(0.04);
		win->plane_dirx = store_planex * cos(0.04) + store_planey * sin(0.04);
		win->plane_diry = -store_planex * sin(0.04) + store_planey * cos(0.04);
		win->start_posx = win->player_x/win->tile;
		win->start_posy = win->player_y/win->tile;
	}
	else if (check == 2)
	{
		win->player_dirx = store_x * cos(0.04) - store_y * sin(0.04);
		win->player_diry = store_x * sin(0.04) + store_y * cos(0.04);
		win->plane_dirx = store_planex * cos(0.04) - store_planey * sin(0.04);
		win->plane_diry = store_planex * sin(0.04) + store_planey * cos(0.04);
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
		if (win->arr[my_may][my_max] != '1' && win->arr[my_may][my_max] != 'D')
			win->player_x += win->player_dirx * 2;
		my_may = (int)(win->player_y + win->player_diry * 5)/win->tile;
		if (win->arr[my_may][my_max] != '1' && win->arr[my_may][my_max] != 'D')
			win->player_y += win->player_diry * 2;
	}
	else if (check == 2)
	{
		my_max = (int)(win->player_x - win->player_dirx * 5)/win->tile;
		my_may = (int)(win->player_y/win->tile);
		if (win->arr[my_may][my_max] != '1' && win->arr[my_may][my_max] != 'D')
			win->player_x -= win->player_dirx * 2;
		my_may = (int)(win->player_y - win->player_diry * 5)/win->tile;
		if (win->arr[my_may][my_max] != '1' && win->arr[my_may][my_max] != 'D')
			win->player_y -= win->player_diry * 2;

	}
	win->start_posx = win->player_x/win->tile;
	win->start_posy = win->player_y/win->tile;
}

void func(void *param)
{
    static bool e_pressing = false;
    t_win *win = param;

    if (mlx_is_key_down(win->mlx, MLX_KEY_E))
    {
        if (!e_pressing)
        {
            handle_doors(win);
            e_pressing = true;
        }
    }
	else
		e_pressing = false;
	if (mlx_is_key_down(win->mlx, MLX_KEY_W))
		ft_mov_press(win, 1);
	else if (mlx_is_key_down(win->mlx, MLX_KEY_S))
		ft_mov_press(win, 2);
	else if (mlx_is_key_down(win->mlx, MLX_KEY_RIGHT))
		ft_rotation(win, 1);
	else if (mlx_is_key_down(win->mlx, MLX_KEY_LEFT))
		ft_rotation(win, 2);
	ft_movement(win, 1);
}

int	ft_move_player(char **arr, t_win *win)
{
	mlx_loop_hook(win->mlx, func, win);
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

int	init_frames(t_win *win)
{
	win->frames.frames[0] = mlx_load_xpm42("./textures/frame_0.xpm42");
	win->frames.frames[1] = mlx_load_xpm42("./textures/frame_1.xpm42");
	win->frames.frames[2] = mlx_load_xpm42("./textures/frame_2.xpm42");
	win->frames.frames[3] = mlx_load_xpm42("./textures/frame_3.xpm42");
	win->frames.frames[4] = mlx_load_xpm42("./textures/frame_4.xpm42");
	win->frames.frames[5] = mlx_load_xpm42("./textures/frame_5.xpm42");
	win->frames.current_frame = 0;
	win->frames.frames_number = 6;
	win->frames.timer = mlx_get_time();
	return (0);
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
	wall_dim.tex.door = mlx_load_xpm42(wall_dim.d);
	if (!wall_dim.tex.east || !wall_dim.tex.north || !wall_dim.tex.west
		|| !wall_dim.tex.south)
		return (1);
	if (init_frames(&win))
		return (0);
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
	close(fd);
	ft_lstclear(&garbage);
	return (0);
}
