/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakroud <aakroud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:27:28 by aakroud           #+#    #+#             */
/*   Updated: 2025/11/10 19:27:39 by aakroud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
