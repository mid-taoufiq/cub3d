/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakroud <aakroud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:16:43 by aakroud           #+#    #+#             */
/*   Updated: 2025/11/08 10:21:13 by aakroud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_player(char c)
{
	if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
		return (1);
	return (0);
}

void	ft_movement_helper(t_win *win, int x, int y, int check)
{
	if (!check)
	{
		win->player_x = (x * win->tile + win->tile / 2);
		win->player_y = (y * win->tile + win->tile / 2);
		win->start_posx = win->player_x / win->tile;
		win->start_posy = win->player_y / win->tile;
	}
	ft_put_img(win->arr, win, 1);
}

void	ft_player_mov(t_win *win, int y, int check, int j)
{
	int	x;
	int	one;
	int	i;

	x = 0;
	one = 0;
	i = 0;
	while (win->arr[j][i])
	{
		if (ft_check_player(win->arr[j][i]))
		{
			ft_movement_helper(win, x, y, check);
			if (!one)
				ft_recast(win, win->arr[j][i], check);
			one = 1;
		}
		x++;
		i++;
	}
}

void	ft_movement(t_win *win, int check)
{
	int		y;
	int		j;
	int		one;

	y = 0;
	j = 0;
	one = 0;
	win->player_tile = win->tile / 2;
	while (win->arr[j])
	{
		ft_player_mov(win, y, check, j);
		y++;
		j++;
	}
}

void	ft_rotate_helper(t_win *win)
{
	win->start_posx = win->player_x / win->tile;
	win->start_posy = win->player_y / win->tile;
}

void	ft_rotate_calculate(t_win *win, int check, double angle)
{
	double	store_rvecx;
	double	store_rvecy;
	double	store_lvecx;
	double	store_lvecy;

	store_rvecx = win->right_vecx;
	store_rvecy = win->right_vecy;
	store_lvecx = win->left_vecx;
	store_lvecy = win->left_vecy;
	if (check == 1)
	{
		win->right_vecx = store_rvecx * cos(angle) + store_rvecy * sin(angle);
		win->right_vecy = -store_rvecx * sin(angle) + store_rvecy * cos(angle);
		win->left_vecx = store_lvecx * cos(angle) + store_lvecy * sin(angle);
		win->left_vecy = -store_lvecx * sin(angle) + store_lvecy * cos(angle);
	}
	else if (check == 2)
	{
		win->right_vecx = store_rvecx * cos(angle) - store_rvecy * sin(angle);
		win->right_vecy = store_rvecx * sin(angle) + store_rvecy * cos(angle);
		win->left_vecx = store_lvecx * cos(angle) - store_lvecy * sin(angle);
		win->left_vecy = store_lvecx * sin(angle) + store_lvecy * cos(angle);
	}
	ft_rotate_helper(win);
}

void	ft_rotation(t_win *win, int check, double angle)
{
	double	store_x;
	double	store_y;
	double	store_planex;
	double	store_planey;

	store_x = win->player_dirx;
	store_y = win->player_diry;
	store_planex = win->plane_dirx;
	store_planey = win->plane_diry;
	if (check == 1)
	{
		win->player_dirx = store_x * cos(angle) + store_y * sin(angle);
		win->player_diry = -store_x * sin(angle) + store_y * cos(angle);
		win->plane_dirx = store_planex * cos(angle) + store_planey * sin(angle);
		win->plane_diry = -store_planex * sin(angle)
			+ store_planey * cos(angle);
	}
	else if (check == 2)
	{
		win->player_dirx = store_x * cos(angle) - store_y * sin(angle);
		win->player_diry = store_x * sin(angle) + store_y * cos(angle);
		win->plane_dirx = store_planex * cos(angle) - store_planey * sin(angle);
		win->plane_diry = store_planex * sin(angle) + store_planey * cos(angle);
	}
	ft_rotate_calculate(win, check, angle);
}

void	handle_doors(t_win *win)
{
	int	px;
	int	py;

	px = (int)win->start_posx;
	py = (int)win->start_posy;
	if (win->door.y != -1 && win->door.x != 1)
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

int	ft_mov_check(t_win *win, int my_max, int my_may, int check)
{
	if (check == 1)
	{
		if (win->arr[my_may][my_max] != '1' && win->arr[my_may][my_max] != 'D')
			return (win->player_x += win->player_dirx * 2, 0);
	}
	else if (check == 2)
	{
		if (win->arr[my_may][my_max] != '1' && win->arr[my_may][my_max] != 'D')
			return (win->player_x -= win->player_dirx * 2, 0);
	}
	else if (check == 3)
	{
		if (win->arr[my_may][my_max] != '1' && win->arr[my_may][my_max] != 'D')
			return (win->player_x += win->left_vecx * 2, 0);
	}
	else if (check == 4)
	{
		if (win->arr[my_may][my_max] != '1' && win->arr[my_may][my_max] != 'D')
			return (win->player_x += win->right_vecx * 2, 0);
	}
	return (1);
}

void	ft_mov_press_helper(t_win *win, int check)
{
	int	my_max;
	int	my_may;

	my_max = (int)(win->player_x + win->left_vecx * 4) / win->tile;
	my_may = (int)(win->player_y + win->left_vecy * 4) / win->tile;
	if (check == 3)
	{
		if (ft_mov_check(win, my_max, (int)(win->player_y / win->tile), check))
			my_max = (int)(win->player_x) / win->tile;
		if (win->arr[my_may][my_max] != '1' && win->arr[my_may][my_max] != 'D')
			win->player_y += win->left_vecy * 2;
	}
	else if (check == 4)
	{
		my_max = (int)(win->player_x + win->right_vecx * 4) / win->tile;
		my_may = (int)(win->player_y + win->right_vecy * 4) / win->tile;
		if (ft_mov_check(win, my_max, (int)(win->player_y / win->tile), check))
			my_max = (int)(win->player_x) / win->tile;
		if (win->arr[my_may][my_max] != '1' && win->arr[my_may][my_max] != 'D')
			win->player_y += win->right_vecy * 2;
	}
}

void	ft_mov_press(t_win *win, int check)
{
	int	my_max;
	int	my_may;

	my_max = (int)(win->player_x + win->player_dirx * 4) / win->tile;
	my_may = (int)(win->player_y + win->player_diry * 4) / win->tile;
	if (check == 1)
	{
		if (ft_mov_check(win, my_max, (int)(win->player_y / win->tile), check))
			my_max = (int)(win->player_x) / win->tile;
		if (win->arr[my_may][my_max] != '1' && win->arr[my_may][my_max] != 'D')
			win->player_y += win->player_diry * 2;
	}
	else if (check == 2)
	{
		my_max = (int)(win->player_x - win->player_dirx * 4) / win->tile;
		my_may = (int)(win->player_y - win->player_diry * 4) / win->tile;
		if (ft_mov_check(win, my_max, (int)(win->player_y / win->tile), check))
			my_max = (int)(win->player_x) / win->tile;
		if (win->arr[my_may][my_max] != '1' && win->arr[my_may][my_max] != 'D')
			win->player_y -= win->player_diry * 2;
	}
	else
		ft_mov_press_helper(win, check);
	win->start_posx = win->player_x / win->tile;
	win->start_posy = win->player_y / win->tile;
}
