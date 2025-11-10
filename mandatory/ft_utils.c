/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakroud <aakroud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:21:51 by aakroud           #+#    #+#             */
/*   Updated: 2025/11/10 18:23:11 by aakroud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_player(char c)
{
	if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
		return (1);
	return (0);
}

// void	ft_movement_helper(t_win *win, int x, int y, int check)
// {
// 	if (!check)
// 	{
// 		win->player_x = (x * win->tile + win->tile / 2);
// 		win->player_y = (y * win->tile + win->tile / 2);
// 		win->start_posx = win->player_x / win->tile;
// 		win->start_posy = win->player_y / win->tile;
// 	}
// 	ft_put_img(win->arr, win, 1);
// }
