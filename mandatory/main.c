/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakroud <aakroud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 11:40:58 by tibarike          #+#    #+#             */
/*   Updated: 2025/11/03 16:03:40 by aakroud          ###   ########.fr       */
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

void key_press(mlx_key_data_t keydata, void *param)
{
	t_win *win;
	win = param;

	if (keydata.key == MLX_KEY_W)
		win->key_pressed = MLX_KEY_W;
	else if (keydata.key == MLX_KEY_S)
		win->key_pressed = MLX_KEY_S;
	else if (keydata.key == MLX_KEY_RIGHT)
		win->key_pressed = MLX_KEY_RIGHT;
	else if (keydata.key == MLX_KEY_LEFT)
		win->key_pressed = MLX_KEY_LEFT;
	else if (keydata.key == MLX_KEY_SPACE)
		win->key_pressed = MLX_KEY_SPACE;
}

void	ft_calculate_lent(t_win *win)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	while (win->arr[i])
	{
		win->column = 0;
		j = 0;
		while (win->arr[i][j])
		{
			j++;
			win->column++;
		}
		win->row++;
		i++;
	}
}

// int	ft_move_player(char **arr, t_win *win)
// {
// 	mlx_key_hook(win->mlx, key_press, win);
// 	mlx_cursor_hook(win->mlx, mouse_handle, (void *)win);
// 	mlx_loop_hook(win->mlx, func, win);
// 	return (0);
// }

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

int	main(int argc, char **argv)
{
	t_wall		wall_dim;
	int			fd;
	char		*line;
	t_garbage	*garbage;
	t_win		win;
	double		frames_now;

	win.tile = 32;
	win.column = 0;
	win.row = 0;
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
	ft_calculate_lent(&win);
	win.mlx = mlx_init(win.width, win.height, "my_mlx", true);
	if (!win.mlx)
		exit (1);
	win.img = mlx_new_image(win.mlx, win.tile*9, win.tile*9);
	if (!win.img)
	{
		mlx_terminate(win.mlx);
		exit (1);
	}
	win.img_3d = mlx_new_image(win.mlx, win.width, win.height);
	if (!win.img_3d)
	{
		mlx_terminate(win.mlx);
		exit (1);
	}
	win.img_player = mlx_new_image(win.mlx, win.tile*9, win.tile*9);
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
	// mlx_terminate(win.mlx);
	if (mlx_image_to_window(win.mlx, win.img_3d, 0, 0) == -1)
	{
		mlx_close_window(win.mlx);
	}
	if (mlx_image_to_window(win.mlx, win.img, 0, 0) == -1)
	{
		mlx_close_window(win.mlx);
	}
	if (mlx_image_to_window(win.mlx, win.img_player, 0, 0) == -1)
	{
		mlx_close_window(win.mlx);
	}
	mlx_loop(win.mlx);
	mlx_terminate(win.mlx);
	close(fd);
	ft_lstclear(&garbage);
	return (0);
}
