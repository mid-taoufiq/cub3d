/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:20:00 by aakroud           #+#    #+#             */
/*   Updated: 2025/11/15 14:02:00 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_rotate_helper(t_win *win)
{
	win->start_posx = win->player_x / win->tile;
	win->start_posy = win->player_y / win->tile;
}

static void	ft_rotate_calculate(t_win *win, int check, double angle)
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
	if (win->door.y != -1 && win->door.x != -1)
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

void	ft_movement_helper(t_win *win, int x, int y, int check)
{
	if (!check)
	{
		win->player_x = (x * win->tile + win->tile / 2);
		win->player_y = (y * win->tile + win->tile / 2);
		win->start_posx = win->player_x / win->tile;
		win->start_posy = win->player_y / win->tile;
	}
	ft_put_img(win->arr, win);
}
