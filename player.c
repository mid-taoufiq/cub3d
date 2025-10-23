#include "cub3d.h"

int	ft_color(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	ft_two_d_map(t_win *win, double ray_Dirx, double ray_Diry, int check)
{
	double	draw_x;
	double	draw_y;
	int		initial1;
	int		initial2;
	int		test;

	draw_x = 0.0;
	draw_y = 0.0;
	initial1 = win->middle_x;
	initial2 = win->middle_y;
	test = 0;
	if (ray_Dirx == win->player_dirx && ray_Diry == win->player_diry)
	{
		while (test < 20)
		{
			draw_x = initial1 + ray_Dirx * test;
			draw_y = initial2 + ray_Diry * test;
			if (draw_x < 0 || draw_y < 0)
				break ;
			mlx_put_pixel(win->img_player,
				draw_x, draw_y, ft_color(0, 0, 0, 255));
			test += 1;
		}
	}
}

void	ft_clear_img(t_win *win, mlx_image_t *img)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < win->height)
	{
		x = 0;
		while (x < win->width)
		{
			mlx_put_pixel(img, x, y, ft_color(0, 0, 0, 0));
			x++;
		}
		y++;
	}
}

void	func(mlx_key_data_t keydata, void *param)
{
	t_win	*win;

	win = (t_win *)param;
	if (keydata.key == MLX_KEY_W)
		ft_mov_press(win, 1);
	else if (keydata.key == MLX_KEY_S)
		ft_mov_press(win, 2);
	if (keydata.key == MLX_KEY_RIGHT)
	{
		ft_clear_img(win, win->img);
		ft_clear_img(win, win->img_player);
		ft_rotation(win, 1);
		ft_movement(win, 1);
	}
	else if (keydata.key == MLX_KEY_LEFT)
	{
		ft_clear_img(win, win->img);
		ft_clear_img(win, win->img_player);
		ft_rotation(win, 2);
		ft_movement(win, 1);
	}
}

void	ft_calculate_lent(t_win *win, char **arr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	win->column = 0;
	win->row = 0;
	while (arr[i])
	{
		j = 0;
		win->column = 0;
		while (arr[i][j])
		{
			j++;
			win->column++;
		}
		win->row++;
		i++;
	}
}

int	ft_move_player(char **arr, t_win *win)
{
	mlx_key_hook(win->mlx, func, win);
	return (0);
}
