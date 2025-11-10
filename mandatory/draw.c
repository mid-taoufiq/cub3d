/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakroud <aakroud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:17:05 by aakroud           #+#    #+#             */
/*   Updated: 2025/11/10 16:47:39 by aakroud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_recto(int x, int y, int color, t_win win)
{
	int	start_x;
	int	start_y;

	start_x = x;
	start_y = y;
	while (y < start_y + win.tile)
	{
		x = start_x;
		while (x < start_x + win.tile)
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
	while (y < start_y + win.player_tile - 1)
	{
		x = start_x;
		while (x < start_x + win.player_tile - 1)
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
	while (y < start_y + win.tile / 3)
	{
		x = start_x;
		while (x < start_x + win.tile / 3)
		{
			mlx_put_pixel(win.img, x, y, color);
			x++;
		}
		y++;
	}
}

void	ft_recto_helper(t_win *win, int x, int y, int color)
{
	ft_recto(x * win->tile, y * win->tile, color, *win);
}

void	ft_draw_case(t_win *win, int x, int y)
{
	if (win->map_startx == (int)win->start_posx
		&& win->map_starty == (int)win->start_posy)
	{
		if (win->arr[win->map_starty][win->map_startx] == 'O')
			ft_recto_helper(win, x, y, ft_color(0, 255, 0, 255));
		else
			ft_recto_helper(win, x, y, ft_color(30, 144, 255, 255));
		ft_recto_player(win->middle_x - win->player_tile / 2,
			win->middle_y - win->player_tile / 2,
			ft_color(255, 0, 0, 255), *win);
		if (win->player_x >= 0 && win->player_y >= 0)
			mlx_put_pixel(win->img_player, win->middle_x, win->middle_y,
				ft_color(0, 0, 0, 255));
	}
	else if (win->arr[win->map_starty][win->map_startx] == '1')
		ft_recto_helper(win, x, y, ft_color(58, 58, 58, 255));
	else if (win->arr[win->map_starty][win->map_startx] == 'D')
		ft_recto_helper(win, x, y, ft_color(128, 128, 128, 255));
	else if (win->arr[win->map_starty][win->map_startx] == 'O')
		ft_recto_helper(win, x, y, ft_color(0, 255, 0, 255));
	else
		ft_recto_helper(win, x, y, ft_color(30, 144, 255, 255));
}

void	ft_put_img_init(t_win *win)
{
	win->middle_x = (win->tile * 9) / 2;
	win->middle_y = (win->tile * 9) / 2;
	win->map_startx = (int)win->start_posx - 4;
	win->map_starty = (int)win->start_posy - 4;
	win->map_endx = (int)win->start_posx + 4;
	win->map_endy = (int)win->start_posy + 4;
}

void	ft_put_img(char **arr, t_win *win, int check)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	ft_put_img_init(win);
	if (!arr || !*arr)
		return ;
	while (win->map_starty <= win->map_endy)
	{
		win->map_startx = (int)win->start_posx - 4;
		x = 0;
		while (win->map_startx <= win->map_endx)
		{
			if (win->map_startx >= 0 && win->map_starty >= 0
				&& win->map_startx < win->column && win->map_starty < win->row)
				ft_draw_case(win, x, y);
			else
				ft_recto_helper(win, x, y, ft_color(58, 58, 58, 255));
			x++;
			win->map_startx++;
		}
		y++;
		win->map_starty++;
	}
}
