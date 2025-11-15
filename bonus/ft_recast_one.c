/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recast_one.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:12:12 by aakroud           #+#    #+#             */
/*   Updated: 2025/11/15 12:14:39 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_player_dir_helper(t_win *win, int check)
{
	if (check == 1)
	{
		win->left_vecx = 0;
		win->left_vecy = -1;
		win->right_vecx = 0;
	}
	else if (check == 2)
	{
		win->left_vecx = 0;
		win->left_vecy = 1;
		win->right_vecx = 0;
	}
	else if (check == 3)
	{
		win->left_vecx = 1;
		win->left_vecy = 0;
		win->right_vecx = -1;
	}
	else if (check == 4)
	{
		win->left_vecx = -1;
		win->left_vecy = 0;
		win->right_vecx = 1;
	}
}

void	ft_player_dir(t_win *win, int check)
{
	if (check == 1)
	{
		win->player_dirx = -1;
		win->player_diry = 0;
		win->right_vecy = 1;
	}
	else if (check == 2)
	{
		win->player_dirx = 1;
		win->player_diry = 0;
		win->right_vecy = -1;
	}
	else if (check == 3)
	{
		win->player_dirx = 0;
		win->player_diry = -1;
		win->right_vecy = 0;
	}
	else if (check == 4)
	{
		win->player_dirx = 0;
		win->player_diry = 1;
		win->right_vecy = 0;
	}
	ft_player_dir_helper(win, check);
}

void	ft_recast_check(t_win *win, char c)
{
	if (c == 'W')
	{
		ft_player_dir(win, 1);
		win->plane_dirx = 0;
		win->plane_diry = 0.66;
	}
	else if (c == 'E')
	{
		ft_player_dir(win, 2);
		win->plane_dirx = 0;
		win->plane_diry = -0.66;
	}
	if (c == 'N')
	{
		ft_player_dir(win, 3);
		win->plane_dirx = -0.66;
		win->plane_diry = 0;
	}
	if (c == 'S')
	{
		ft_player_dir(win, 4);
		win->plane_dirx = 0.66;
		win->plane_diry = 0;
	}
}

void	handle_frames(t_win *win)
{
	double	frame_timer;

	frame_timer = mlx_get_time();
	if (win->frames.img != NULL)
		mlx_delete_image(win->mlx, win->frames.img);
	win->frames.img = mlx_texture_to_image(win->mlx,
			&win->frames.frames[win->frames.current_frame]->texture);
	if (!win->frames.img)
		return (mlx_terminate(win->mlx),
			free_window(win, &win->garbage, win->fd), exit(1));
	win->frames.x = win->frames.img->width - 250;
	win->frames.y = win->frames.img->height - 200;
	if (mlx_image_to_window(win->mlx, win->frames.img,
			win->frames.x, win->frames.y) == -1)
		return (mlx_terminate(win->mlx),
			free_window(win, &win->garbage, win->fd), exit(1));
	if (frame_timer - win->frames.timer > 0.05)
	{
		win->frames.timer = frame_timer;
		win->frames.current_frame++;
		if (win->frames.current_frame == win->frames.frames_number)
			win->frames.current_frame = 0;
	}
}

void	ft_recast(t_win *win, char c, int check)
{
	if (c == 'W')
	{
		if (!check)
			ft_recast_check(win, c);
		ft_recast_helper(win);
	}
	if (c == 'E')
	{
		if (!check)
			ft_recast_check(win, c);
		ft_recast_helper(win);
	}
	if (c == 'N')
	{
		if (!check)
			ft_recast_check(win, c);
		ft_recast_helper(win);
	}
	if (c == 'S')
	{
		if (!check)
			ft_recast_check(win, c);
		ft_recast_helper(win);
	}
	handle_frames(win);
}
