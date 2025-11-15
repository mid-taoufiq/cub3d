/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:16:43 by aakroud           #+#    #+#             */
/*   Updated: 2025/11/15 14:03:21 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_player_mov(t_win *win, int y, int check, int j)
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

static int	ft_mov_check(t_win *win, int my_max, int my_may, int check)
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

static void	ft_mov_press_helper(t_win *win, int check)
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
