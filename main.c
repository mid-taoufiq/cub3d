/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakroud <aakroud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 11:40:58 by tibarike          #+#    #+#             */
/*   Updated: 2025/09/09 12:11:25 by aakroud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	struct_init(t_wall *wall_dim)
{
	wall_dim->no = NULL;
	wall_dim->we = NULL;
	wall_dim->ea = NULL;
	wall_dim->so = NULL;
	wall_dim->no_filled = 0;
	wall_dim->we_filled = 0;
	wall_dim->ea_filled = 0;
	wall_dim->so_filled = 0;
	wall_dim->ceiling[0] = 0;
	wall_dim->ceiling[1] = 0;
	wall_dim->ceiling[2] = 0;
	wall_dim->floor[0] = 0;
	wall_dim->floor[1] = 0;
	wall_dim->floor[2] = 0;
}

int	ft_check_player(char c)
{
	if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
		return (1);
	return (0);
}

int	parsing(char *line, int fd, t_wall *wall_dim, t_garbage **garbage)
{
	int	return_value;

	while (1)
	{
		line = get_next_line(fd, garbage);
		if (!line)
			return (1);
		if (check_empty_line(line))
			continue ;
		return_value = add_dimensions(wall_dim, line, garbage);
		if (!return_value)
			return (0);
		else if (return_value == 2)
			continue ;
		return_value = add_colors(wall_dim, line, garbage);
		if (!return_value)
			return (0);
		else if (return_value == 2)
			continue ;
	}
	return (1);
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

void	ft_line(t_win win, int desired_x, int limit_y, int (*ft_color)(int r, int g, int b, int a))
{
	int	y;

	y = 0;
	while (y < limit_y)
	{
		mlx_put_pixel(win.img, desired_x, y, ft_color);
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

void	ft_recast(t_win *win, char c)
{
	double	now;
	double	before;
	int		x;
	double	camera;
	double	ray_Dirx;
	double	ray_Diry;
	double draw_x;
	double draw_y;

	now = 0;
	before = 0;
	x = 0;
	camera = 0;
	ray_Dirx = 0;
	ray_Diry = 0;
	if (c == 'E')
	{
		win->player_dirx = -1;
		win->player_diry = 0;
		win->plane_dirx = 0;
		win->plane_diry = 0.66;
		double initial1; 
		double initial2;
		while (x < win->width)
		{
			camera = 2 * x / (double)win->width - 1;
			ray_Dirx = win->player_dirx + win->plane_dirx * camera;
			ray_Diry = win->player_diry + win->plane_diry * camera;
			// printf("this is %.1f and %.1f\n", ray_Dirx, ray_Diry);
			draw_x = win->player_x;//just for testing
			draw_y = win->player_y;
			initial1 = win->player_x;//just for testing
			initial2 = win->player_y;
			double test = 0;
			while (test < 50)
			{
				draw_x = initial1 + ray_Dirx * test;
				draw_y = initial2 + ray_Diry * test;
				mlx_put_pixel(win->img_player, draw_x, draw_y, ft_color(0,0,0,255));
				test += 1;
			}
			x++;
		}
	}
	else if (c == 'N')
	{
		win->player_dirx = 0;
		win->player_diry = -1;
		win->plane_dirx = -0.66;
		win->plane_diry = 0;
		double initial1; 
		double initial2;
		while (x < win->width)
		{
			camera = 2 * x / (double)win->width - 1;
			ray_Dirx = win->player_dirx + win->plane_dirx * camera;
			ray_Diry = win->player_diry + win->plane_diry * camera;
			// printf("this is %.1f and %.1f\n", ray_Dirx, ray_Diry);
			draw_x = win->player_x;//just for testing
			draw_y = win->player_y;
			initial1 = win->player_x;//just for testing
			initial2 = win->player_y;
			double test = 0;
			while (test < 50)
			{
				draw_x = initial1 + ray_Dirx * test;
				draw_y = initial2 + ray_Diry * test;
				mlx_put_pixel(win->img_player, draw_x, draw_y, ft_color(0,0,0,255));
				test += 1;
			}
			x++;
		}
	}
	else if (c == 'S')
	{
		win->player_dirx = 0;
		win->player_diry = 1;
		win->plane_dirx = -0.66;
		win->plane_diry = 0;
		double initial1; 
		double initial2;
		while (x < win->width)
		{
			camera = 2 * x / (double)win->width - 1;
			ray_Dirx = win->player_dirx + win->plane_dirx * camera;
			ray_Diry = win->player_diry + win->plane_diry * camera;
			printf("this is %.1f and %.1f\n", ray_Dirx, ray_Diry);
			draw_x = win->player_x;//just for testing
			draw_y = win->player_y;
			initial1 = win->player_x;//just for testing
			initial2 = win->player_y;
			double test = 0;
			while (test < 50)
			{
				draw_x = initial1 + ray_Dirx * test;
				draw_y = initial2 + ray_Diry * test;
				mlx_put_pixel(win->img_player, draw_x, draw_y, ft_color(0,0,0,255));
				test += 1;
			}
			x++;
		}
	}
	else if (c == 'W')
	{
		win->player_dirx = 1;
		win->player_diry = 0;
		win->plane_dirx = 0;
		win->plane_diry = 0.66;
		double initial1; 
		double initial2;
		while (x < win->width)
		{
			camera = 2 * x / (double)win->width - 1;
			ray_Dirx = win->player_dirx + win->plane_dirx * camera;
			ray_Diry = win->player_diry + win->plane_diry * camera;
			printf("this is %.1f and %.1f\n", ray_Dirx, ray_Diry);
			draw_x = win->player_x;//just for testing
			draw_y = win->player_y;
			initial1 = win->player_x;//just for testing
			initial2 = win->player_y;
			double test = 0;
			while (test < 50)
			{
				draw_x = initial1 + ray_Dirx * test;
				draw_y = initial2 + ray_Diry * test;
				mlx_put_pixel(win->img_player, draw_x, draw_y, ft_color(0,0,0,255));
				test += 1;
			}
			x++;
		}
	}
}

void	ft_movement(t_win *win, int check)
{
	int		x;
	int		y;
	int		i;
	int		j;
	int		player_tile;
	char	c;
	int		one;

	x = 0;
	y = 0;
	i = 0;
	j = 0;
	one = 0;
	player_tile = win->tile/4;
	while (win->arr[j])
	{
		i = 0;
		x = 0;
		while (win->arr[j][i])
		{
			// printf("enterd\n");
			if (ft_check_player(win->arr[j][i]))
			{
				c = win->arr[j][i];
				if (!check)
				{
					win->player_x = (x * win->tile + win->tile/2);
					win->player_y = (y * win->tile + win->tile/2);
					win->start_posx = win->player_x/win->tile;
					win->start_posy = win->player_y/win->tile;
					// printf("thsi is them %.1f and %.1f\n", win->start_posx, win->start_posy);
				}
				ft_recto_player(win->player_x - player_tile/2, win->player_y -player_tile/2, ft_color(255, 0, 0, 255), *win);
				if (win->player_x >= 0 && win->player_y >= 0)
					mlx_put_pixel(win->img_player, (int)win->player_x, (int)win->player_y, ft_color(0, 0, 0, 255));
				// if (!one)
				// 	ft_recast(win, 'W');
				one = 1;
			}
			x += 1;
			i++;
		}
		y += 1;
		j++;
	}
}

void	ft_remove_line(t_win *win)
{
	int	x;
	int	y;
	int	i;
	int	j;

	x = 0;
	y = 0;
	i = 0;
	j = 0;
	while (win->arr[j])
	{
		i = 0;
		x = 0;
		while (win->arr[j][i])
		{
			if (ft_check_player(win->arr[j][i]))
				ft_line(*win, x * win->tile + win->tile/2, y * win->tile + win->tile/2, ft_color(0, 0, 0, 255));
			x += 1;
			i++;
		}
		y += 1;
		j++;
	}
}

void	ft_clear_img(t_win *win)
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
			mlx_put_pixel(win->img_player, x, y, ft_color(0,0,0,0));
			x++;
		}
		y++;
	}
}

void func(mlx_key_data_t keydata, void *param)
{
	t_win	*win;

	win = (t_win *)param;
	if (keydata.key == MLX_KEY_W)
	{
		ft_clear_img(win);
		win->player_y -= win->tile/16;
		win->start_posy = win->player_y/win->tile;
		ft_movement(win, 1);
	}
	else if (keydata.key == MLX_KEY_S)
	{
		ft_clear_img(win);
		win->player_y += win->tile/16;
		win->start_posy = win->player_y/win->tile;
		ft_movement(win, 1);
	}
	else if (keydata.key == MLX_KEY_A)
	{
		ft_clear_img(win);
		win->player_x -= win->tile/16;
		win->start_posx = win->player_x/win->tile;
		ft_movement(win, 1);
	}
	else if (keydata.key == MLX_KEY_D)
	{
		ft_clear_img(win);
		win->player_x += win->tile/16;
		win->start_posx = win->player_x/win->tile;
		ft_movement(win, 1);
	}
}

int	ft_move_player(char **arr, t_win *win)
{
	mlx_key_hook(win->mlx, func, win);
	// mlx_loop_hook(win->mlx, f, win);
}

char	*ft_strdupo(char *s1)
{
	int		i;
	char	*dup;

	i = 0;
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
					printf("this is x %d and y %d\n", win->player_x, y);
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
	dup = malloc(sizeof(char *) * 6);
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
	t_garbage	*garbage;
	t_win		win;
	char		*map[] = {"11111111",
			"10000001",
			"10N00101",
			"10000001",
			"11111111",
			NULL};;
	win.arr = ft_alloc_arr(map);
	win.tile = 64;
	// struct_init(&wall_dim);
	// // if (argc != 2)
	// // 	return (1);
	// garbage = NULL;
	// fd = open(argv[1], O_RDONLY);
	// if (!parsing(NULL, fd, &wall_dim, &garbage))
	// 	return (close(fd), ft_lstclear(&garbage), 1);
	win.width = 700;
	win.height = 700;
	win.mlx = mlx_init(700, 700, "my_mlx", true);
	if (!win.mlx)
		exit (1);
	win.img = mlx_new_image(win.mlx, 700, 700);
	if (!win.img)
	{
		mlx_terminate(win.mlx);
		exit (1);
	}
	win.img_player = mlx_new_image(win.mlx, 700, 700);
	if (!win.img_player)
	{
		mlx_terminate(win.mlx);
		exit (1);
	}
	ft_put_img(win.arr, &win, 1);
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
