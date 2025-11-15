/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 11:40:58 by tibarike          #+#    #+#             */
/*   Updated: 2025/11/15 15:27:50 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_window(t_win *win, t_garbage **garbage, int fd)
{
	if (win->mlx)
		mlx_terminate(win->mlx);
	free_textures(win);
	close(fd);
	ft_lstclear(garbage);
}

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

static void	ft_calculate_lent(t_win *win)
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

static int	raycasting(t_win *win)
{
	ft_calculate_lent(win);
	win->mlx = mlx_init(win->width, win->height, "my_mlx", false);
	if (!win->mlx)
		return (1);
	win->img = mlx_new_image(win->mlx, win->tile * 9, win->tile * 9);
	if (!win->img)
		return (1);
	win->img_3d = mlx_new_image(win->mlx, win->width, win->height);
	if (!win->img_3d)
		return (1);
	win->img_player = mlx_new_image(win->mlx, win->tile * 9, win->tile * 9);
	if (!win->img_player)
		return (1);
	ft_movement(win, 0);
	ft_move_player(win);
	if (mlx_image_to_window(win->mlx, win->img_3d, 0, 0) == -1
		|| mlx_image_to_window(win->mlx, win->img, 0, 0) == -1
		|| mlx_image_to_window(win->mlx, win->img_player, 0, 0) == -1)
		mlx_close_window(win->mlx);
	mlx_loop(win->mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	t_wall		wall_dim;
	t_win		win;

	win.tile = 32;
	win.column = 0;
	win.row = 0;
	if (argc != 2 || !check_extansion(argv[1], ".cub", 0))
		return (write(2, "Error\nnot valid arguments\n", 27), 1);
	win.garbage = NULL;
	win.fd = open(argv[1], O_RDONLY);
	if (win.fd < 0)
		return (perror(argv[1]), 1);
	if (parsing(win.fd, &win.garbage, &wall_dim))
		return (close(win.fd), ft_lstclear(&win.garbage), 1);
	init_window(&win, &wall_dim);
	if (init_walltex(&win))
		return (close(win.fd), ft_lstclear(&win.garbage), 1);
	if (raycasting(&win))
		return (free_window(&win, &win.garbage, win.fd), 1);
	return (free_window(&win, &win.garbage, win.fd), 0);
}
