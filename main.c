/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakroud <aakroud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 11:40:58 by tibarike          #+#    #+#             */
/*   Updated: 2025/09/02 11:29:10 by aakroud          ###   ########.fr       */
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

int	ft_check_player(char c)
{
	if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
		return (1);
	return (0);
}

void	ft_put_img(char **arr, t_win win)
{
	int	x;
	int	y;
	int	i;
	int	j;

	x = 0;
	y = 0;
	i = 0;
	j = 0;
	// while (win.arr[i])
	// {
	// 	printf("%s\n", win.arr[i]);
	// 	i++;
	// }
	if (!arr || !*arr)
		return ;
	while (arr[j])
	{
		i = 0;
		x = 0;
		while (arr[j][i])
		{
			// printf("no %d and i %d\n", j, i);
			if (arr[j][i] == '1')
			{
				ft_recto(x * win.tile, y * win.tile, ft_color(0, 0, 255, 255), win);
			}
			else if (ft_check_player(arr[j][i]))
			{
				ft_recto(x * win.tile, y * win.tile, ft_color(255, 0, 0, 255), win);
				mlx_put_pixel(win.img, x * win.tile + win.tile/2, y * win.tile + win.tile/2, ft_color(0, 0, 0, 255));
				ft_line(win, x * win.tile + win.tile/2, y * win.tile + win.tile/2, ft_color(0, 255, 0, 255));
			}
			else
				ft_recto(x * win.tile, y * win.tile, ft_color(255, 255, 0, 255), win);
			x += 1;
			i++;
		}
		y += 1;
		j++;
	}
}

void	ft_print_arr(char **arr)
{
	int i = 0;
	if (!arr[i])
		printf("hell nah\n");
	while (arr[i])
	{
		printf("this is ad %s\n", arr[i]);
		i++;
	}
	printf("==============\n");
}

void	ft_redraw(char	**arr, int l)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			if (ft_check_player(arr[i][j]))
			{
				if (l == 1 && arr[i-1][j] != '1')
				{
					arr[i-1][j] = arr[i][j];
					arr[i][j] = '0';
					return ;
				}
				else if (l == 2 && arr[i][j+1] != '1')
				{
					arr[i][j+1] = arr[i][j];
					arr[i][j] = '0';
					return ;
				}
				else if (l == 3 && arr[i][j-1] != '1')
				{
					arr[i][j-1] = arr[i][j];
					arr[i][j] = '0';
					return ;
				}
				else if (l == 4 && arr[i+1][j] != '1')
				{
					arr[i+1][j] = arr[i][j];
					arr[i][j] = '0';
					return ;
				}
			}
			j++;
		}
		i++;
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

void func(mlx_key_data_t keydata, void *param)
{
	t_win	*win;

	win = (t_win *)param;
	if (keydata.key == MLX_KEY_W)
	{
		ft_remove_line(win);
		ft_redraw(win->arr, 1);
		ft_put_img(win->arr, *win);
	}
	else if (keydata.key == MLX_KEY_S)
	{
		ft_remove_line(win);
		ft_redraw(win->arr, 4);
		ft_put_img(win->arr, *win);
	}
	else if (keydata.key == MLX_KEY_A)
	{
		ft_remove_line(win);
		ft_redraw(win->arr, 3);
		ft_put_img(win->arr, *win);
	}
	else if (keydata.key == MLX_KEY_D)
	{
		ft_remove_line(win);
		ft_redraw(win->arr, 2);
		ft_put_img(win->arr, *win);
	}
}

// void	f(void *param)
// {
// 	t_win	*win;
// 	win = (t_win *)param;
// 	ft_put_img(win->arr, *win);
// }

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
	ft_put_img(win.arr, win);
	ft_move_player(win.arr, &win);
	if (mlx_image_to_window(win.mlx, win.img, 0, 0) == -1)
	{
		mlx_terminate(win.mlx);
		exit (1);
	}
	mlx_loop(win.mlx);
	return (0);
}
