/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakroud <aakroud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 11:40:58 by tibarike          #+#    #+#             */
/*   Updated: 2025/11/08 11:44:07 by aakroud          ###   ########.fr       */
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
	return (0);
}

int	main(int argc, char **argv)
{
	t_wall		wall_dim;
	int			fd;
	char		*line;
	t_garbage	*garbage;
	t_win		win;

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
