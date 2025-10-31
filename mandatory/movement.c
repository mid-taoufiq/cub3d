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
		win->past_posx = (int)win->start_posx;
		win->past_posy = (int)win->start_posy;
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

void	ft_rotation(t_win *win, int check, double angle)
{
	double	store_x;
	double	store_y;
	double	store_planex;
	double	store_planey;
	double	store_rvecx;
	double	store_rvecy;
	double	store_lvecx;
	double	store_lvecy;

	store_x = win->player_dirx;
	store_y = win->player_diry;
	store_planex = win->plane_dirx;
	store_planey = win->plane_diry;
	store_rvecx = win->right_vecx;
	store_rvecy = win->right_vecy;
	store_lvecx = win->left_vecx;
	store_lvecy = win->left_vecy;
	if (check == 1)
	{
		win->player_dirx = store_x * cos(angle) + store_y * sin(angle);
		win->player_diry = -store_x * sin(angle) + store_y * cos(angle);
		win->plane_dirx = store_planex * cos(angle) + store_planey * sin(angle);
		win->plane_diry = -store_planex * sin(angle) + store_planey * cos(angle);
		win->right_vecx = store_rvecx * cos(angle) + store_rvecy * sin(angle);
		win->right_vecy = -store_rvecx * sin(angle) + store_rvecy * cos(angle);
		win->left_vecx = store_lvecx * cos(angle) + store_lvecy * sin(angle);
		win->left_vecy = -store_lvecx * sin(angle) + store_lvecy * cos(angle);
		ft_rotate_helper(win);
	}
	else if (check == 2)
	{
		win->player_dirx = store_x * cos(angle) - store_y * sin(angle);
		win->player_diry = store_x * sin(angle) + store_y * cos(angle);
		win->plane_dirx = store_planex * cos(angle) - store_planey * sin(angle);
		win->plane_diry = store_planex * sin(angle) + store_planey * cos(angle);
		win->right_vecx = store_rvecx * cos(angle) - store_rvecy * sin(angle);
		win->right_vecy = store_rvecx * sin(angle) + store_rvecy * cos(angle);
		win->left_vecx = store_lvecx * cos(angle) - store_lvecy * sin(angle);
		win->left_vecy = store_lvecx * sin(angle) + store_lvecy * cos(angle);
		ft_rotate_helper(win);
	}
}

void	ft_mov_press(t_win *win, int check)
{
	int	my_max;
	int	my_may;

	my_max = 0;
	my_may = 0;
	if (check == 1)
	{
		my_max = (int)(win->player_x + win->player_dirx * 3)/win->tile;
		my_may = (int)(win->player_y/win->tile);
		if (win->arr[my_may][my_max] != '1')
			win->player_x += win->player_dirx * 2;
		my_may = (int)(win->player_y + win->player_diry * 3)/win->tile;
		if (win->arr[my_may][my_max] != '1')
			win->player_y += win->player_diry * 2;
		win->start_posx = win->player_x/win->tile;
		win->start_posy = win->player_y/win->tile;
	}
	else if (check == 2)
	{
		my_max = (int)(win->player_x - win->player_dirx * 3)/win->tile;
		my_may = (int)(win->player_y/win->tile);
		if (win->arr[my_may][my_max] != '1')
			win->player_x -= win->player_dirx * 2;
		my_may = (int)(win->player_y - win->player_diry * 3)/win->tile;
		if (win->arr[my_may][my_max] != '1')
			win->player_y -= win->player_diry * 2;
		win->start_posx = win->player_x/win->tile;
		win->start_posy = win->player_y/win->tile;
	}
	else if (check == 3)
	{
		my_max = (int)(win->player_x + win->right_vecx * 3)/win->tile;
		my_may = (int)(win->player_y/win->tile);
		if (win->arr[my_may][my_max] != '1')
			win->player_x += win->right_vecx * 3;
		my_may = (int)(win->player_y + win->right_vecy * 3)/win->tile;
		if (win->arr[my_may][my_max] != '1')
			win->player_y += win->right_vecy * 3;
		win->start_posx = win->player_x/win->tile;
		win->start_posy = win->player_y/win->tile;
	}
	else if (check == 4)
	{
		my_max = (int)(win->player_x + win->left_vecx * 3)/win->tile;
		my_may = (int)(win->player_y/win->tile);
		if (win->arr[my_may][my_max] != '1')
			win->player_x += win->left_vecx * 3;
		my_may = (int)(win->player_y + win->left_vecy * 3)/win->tile;
		if (win->arr[my_may][my_max] != '1')
			win->player_y += win->left_vecy * 3;
		win->start_posx = win->player_x/win->tile;
		win->start_posy = win->player_y/win->tile;
	}
}

