#include "cub3d.h"

int	ft_color(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

// void	ft_clear_img(t_win *win, mlx_image_t *img)
// {
// 	int	x;
// 	int	y;

// 	x = 0;
// 	y = 0;
// 	while (y < 64)
// 	{
// 		x = 0;
// 		while (x < 64)
// 		{
// 			mlx_put_pixel(img, x, y, ft_color(0, 0, 0, 0));
// 			x++;
// 		}
// 		y++;
// 	}
// }

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
		while (test < 8)
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

void	func(void *param)
{
	t_win	*win;
	static bool e_pressing = false;

	win = (t_win *)param;
    if (mlx_is_key_down(win->mlx, MLX_KEY_E))
    {
        if (!e_pressing)
        {
            handle_doors(win);
            e_pressing = true;
        }
    }
	else
		e_pressing = false;
	if (mlx_is_key_down(win->mlx, MLX_KEY_W))
		ft_mov_press(win, 1);
	if (mlx_is_key_down(win->mlx, MLX_KEY_S))
		ft_mov_press(win, 2);
	if (mlx_is_key_down(win->mlx, MLX_KEY_A))
		ft_mov_press(win, 3);
	if (mlx_is_key_down(win->mlx, MLX_KEY_D))
		ft_mov_press(win, 4);
	if (mlx_is_key_down(win->mlx, MLX_KEY_RIGHT))
		ft_rotation(win, 1, 0.04);
	else if (mlx_is_key_down(win->mlx, MLX_KEY_LEFT))
		ft_rotation(win, 2, 0.04);
	if (mlx_is_key_down(win->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(win->mlx);
		return ;
	}
	ft_movement(win, 1);
}

void	mouse_handle(double xpos, double ypos, void *param)
{
	t_win *win;
	int		x_center;
	double	r;

	win = (t_win *)param;
	x_center = win->width/2;
	r = (xpos - x_center) * 0.001;
	if (r > 0)
		ft_rotation(win, 1, r);
	else
	{
		r = -r;
		ft_rotation(win, 2, r);
	}
	mlx_set_mouse_pos(win->mlx, win->width/2, win->height/2);
}

int	ft_move_player(char **arr, t_win *win)
{
	mlx_set_cursor_mode(win->mlx, MLX_MOUSE_DISABLED);
	mlx_cursor_hook(win->mlx, mouse_handle, (void *)win);
	mlx_loop_hook(win->mlx, func, win);
	// mlx_key_hook(win->mlx, func, win);
	return (0);
}
