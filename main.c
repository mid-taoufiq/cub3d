/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakroud <aakroud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 11:40:58 by tibarike          #+#    #+#             */
/*   Updated: 2025/10/22 16:10:24 by aakroud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_extansion(char *line, char *extansion)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	if (line[i - 1] != extansion[3] || line[i - 2] != extansion[2]
		|| line[i - 3] != extansion[1] || line[i - 4] != extansion[0])
		return (0);
	return (1);
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
	win.tile = 32;
	struct_init(&wall_dim);
	line = NULL;
	if (argc != 2 || !check_extansion(argv[1], ".cub"))
		return (write(2, "not valid arguments\n", 21), 1);
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
	ft_calculate_lent(&win, win.arr);
	win.width = 1400;
	win.height = 800;
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
	win.img_3d = mlx_new_image(win.mlx, win.width, win.height);
	if (!win.img_3d)
	{
		mlx_terminate(win.mlx);
		exit (1);
	}
	ft_movement(&win, 0);
	ft_move_player(win.arr, &win);
	if (mlx_image_to_window(win.mlx, win.img_3d, 0, 0) == -1)
	{
		mlx_terminate(win.mlx);
		exit (1);
	}
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
