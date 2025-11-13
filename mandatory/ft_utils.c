/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:21:51 by aakroud           #+#    #+#             */
/*   Updated: 2025/11/13 15:52:58 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_window(t_win *win, t_wall *wall_dim)
{
	win->arr = wall_dim->map;
	win->width = WIDTH;
	win->height = HEIGHT;
	win->wall_dim = wall_dim;
}

int	ft_check_player(char c)
{
	if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
		return (1);
	return (0);
}

int	ft_color(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}
