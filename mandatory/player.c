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
	else if (keydata.key == MLX_KEY_A)
	{
		ft_mov_press(win, 3);
	}
	else if (keydata.key == MLX_KEY_D)
	{
		ft_mov_press(win, 4);
	}
	if (keydata.key == MLX_KEY_RIGHT)
	{
		ft_clear_img(win, win->img_3d);
		ft_clear_img(win, win->img_player);
		ft_rotation(win, 1, 0.1);
		ft_movement(win, 1);
	}
	else if (keydata.key == MLX_KEY_LEFT)
	{
		ft_clear_img(win, win->img_3d);
		ft_clear_img(win, win->img_player);
		ft_rotation(win, 2, 0.1);
		ft_movement(win, 1);
	}
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(win->mlx);
}

void	mouse_handle(double xpos, double ypos, void *param)
{
	t_win *win;
	int		x_center;
	int		y_center;

	win = (t_win *)param;
	x_center = win->width/2;
	y_center = win->height/2;
	ft_clear_img(win, win->img_3d);
	ft_clear_img(win, win->img_player);
	if ((x_center - (int)xpos) > 0)
	{
		ft_rotation(win, 2, 0.1);
		ft_movement(win, 1);
	}
	else
	{
		ft_rotation(win, 1, 0.1);
		ft_movement(win, 1);
	}
	mlx_set_mouse_pos(win->mlx, win->width/2, win->height/2);
}

int	ft_move_player(char **arr, t_win *win)
{
	// mlx_set_cursor_mode(win->mlx, MLX_MOUSE_DISABLED);
	mlx_cursor_hook(win->mlx, mouse_handle, (void *)win);
	mlx_key_hook(win->mlx, func, win);
	return (0);
}
