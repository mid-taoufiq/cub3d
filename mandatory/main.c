/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakroud <aakroud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 11:40:58 by tibarike          #+#    #+#             */
/*   Updated: 2025/11/10 17:55:07 by aakroud          ###   ########.fr       */
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

int	parsing(int fd, t_garbage **garbage, t_wall *wall_dim)
{
	char	*line;

	line = NULL;
	if (!parsing_loop(line, fd, wall_dim, garbage))
		return (1);
	if (!check_remaining(fd, line, wall_dim, garbage))
		return (1);
	if (!parse_map(wall_dim, 0))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_wall		wall_dim;
	int			fd;
	t_garbage	*garbage;
	t_win		win;

	win.tile = 32;
	win.column = 0;
	win.row = 0;
	struct_init(&wall_dim);
	if (argc != 2 || !check_extansion(argv[1], ".cub", 0))
		return (write(2, "Error\nnot valid arguments\n", 27), 1);
	garbage = NULL;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (perror(argv[1]), 1);
	if (parsing(fd, &garbage, &wall_dim))
		return (close(fd), ft_lstclear(&garbage), 1);
	win.arr = wall_dim.map;
	win.width = WIDTH;
	win.height = HEIGHT;
	win.wall_dim = &wall_dim;
	if (init_frames(&win))
		return (close(fd), ft_lstclear(&garbage), 1);
	if (init_walltex(&win))
		return (free_frames(&win), close(fd), ft_lstclear(&garbage), 1);
	ft_calculate_lent(&win);
	win.mlx = mlx_init(win.width, win.height, "my_mlx", true);
	if (!win.mlx)
		exit (1);
	win.img = mlx_new_image(win.mlx, win.tile * 9, win.tile * 9);
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
	win.img_player = mlx_new_image(win.mlx, win.tile * 9, win.tile * 9);
	if (!win.img_player)
	{
		mlx_terminate(win.mlx);
		exit (1);
	}
	ft_movement(&win, 0);
	ft_move_player(win.arr, &win);
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
	close(fd);
	ft_lstclear(&garbage);
	mlx_terminate(win.mlx);
	return (0);
}
