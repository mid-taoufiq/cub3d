/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakroud <aakroud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 11:35:29 by tibarike          #+#    #+#             */
/*   Updated: 2025/11/15 11:35:48 by aakroud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <stdio.h>
# include <fcntl.h>
# include ".MLX42.h"
# include <math.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define WIDTH 1920
# define HEIGHT 1080

typedef struct s_garbage
{
	void				*address;
	struct s_garbage	*next;
}	t_garbage;

typedef struct s_tex
{
	xpm_t	*north;
	xpm_t	*west;
	xpm_t	*east;
	xpm_t	*south;
	xpm_t	*door;
}	t_tex;

typedef struct s_wall
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*d;
	char	**map;
	char	player_direction;
	int		floor;
	int		ceiling;
	int		no_filled;
	int		we_filled;
	int		ea_filled;
	int		so_filled;
	int		f_filled;
	int		c_filled;
	int		door_filled;
	int		map_filled;
	t_tex	tex;
}	t_wall;

typedef struct s_door
{
	int	x;
	int	y;
}	t_door;

typedef struct s_frames
{
	xpm_t		*frames[6];
	int			current_frame;
	int			frames_number;
	int			x;
	int			y;
	mlx_image_t	*img;
	double		timer;
}	t_frames;

typedef struct s_win
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	mlx_image_t	*img_player;
	int			tile;
	double		player_tile;
	int			width;
	int			height;
	char		**arr;
	double		player_x;
	double		player_y;
	double		player_dirx;
	double		player_diry;
	double		plane_dirx;
	double		plane_diry;
	double		start_posx;
	double		start_posy;
	double		distx;
	double		disty;
	double		distance;
	t_wall		*wall_dim;
	int			column;
	int			row;
	int			middle_x;
	int			middle_y;
	mlx_image_t	*img_3d;
	int			map_startx;
	int			map_starty;
	int			map_endx;
	int			map_endy;
	double		right_vecx;
	double		right_vecy;
	double		left_vecx;
	double		left_vecy;
	t_frames	frames;
	t_door		door;
	int			mx;
	int			my;
	double		deltax;
	double		deltay;
	int			sx;
	int			sy;
	int			is_door;
	int			way;
	int			ps;
	int			pe;
	double		wall_x;
	int			tex_x;
	xpm_t		*tex;
	double		step;
	double		tex_pos;
	int			tex_y;
	uint8_t		*pixel;
	t_garbage	*garbage;
	int			fd;
}	t_win;

void	*ft_malloc(int size, t_garbage **garbage);
char	*ft_strjoin(char *s1, char *s2, t_garbage **garbage);
int		ft_strlen(char *str);
int		ft_strncmp(char *str1, char *str2, int n);
char	*ft_strdup(char *str, t_garbage **garbage);
char	*ft_substr(char *s, int start, int len, t_garbage **garbage);
char	*ft_strtrim(char *s1, char *set, t_garbage **garbage);
char	*ft_strtrimlast(char *s1, char *set, t_garbage **garbage);
int		find_newline(char *str);
char	*get_next_line(int fd, t_garbage **garb);
int		ft_atoi(char *nb);
int		arg_counter(char **arr);
char	**ft_split(char *s, char c, t_garbage **garbage);
int		add_colors(t_wall *wall_dim, char *line, t_garbage **garbage);
int		check_empty_line(char *line);
int		ft_strsearch(char *str, char *search);
int		ft_strsearch2(char *str, char *search);
int		arg_counter(char **arr);
int		add_dimensions(t_wall *wall_dim, char *line, t_garbage **garbage);
void	ft_lstclear(t_garbage **lst);
int		add_to_map(char *line, t_wall *wall_dim, t_garbage **garbage, int fd);
int		check_options(t_wall *wall, int option);
int		parse_map(t_wall *wall, int cp);
int		check_remaining(int fd, char *line, t_wall *wall, t_garbage **garbage);
void	struct_init(t_wall *wall_dim);
int		parsing_loop(char *line, int fd, t_wall *wall_dim, t_garbage **garbage);
int		parsing(int fd, t_garbage **garbage, t_wall *wall_dim);
int		check_extansion(char *line, char *extansion, int option);
int		ft_check_player(char c);
int		ft_color(int r, int g, int b, int a);
void	ft_put_img(char **arr, t_win *win, int check);
void	ft_player(int x, int y, int color, t_win win);
void	ft_recto_player(int x, int y, int color, t_win win);
void	ft_recto(int x, int y, int color, t_win win);
void	ft_recast_helper(t_win *win);
void	ft_recast(t_win *win, char c, int check);
int		ft_move_player(char **arr, t_win *win);
void	ft_calculate_lent(t_win *win);
void	func(void *param);
int		ft_color(int r, int g, int b, int a);
void	ft_rotation(t_win *win, int check, double angle);
void	ft_movement(t_win *win, int check);
int		ft_check_player(char c);
void	ft_mov_press(t_win *win, int check);
void	mouse_handle(double xpos, double ypos, void *param);
int		init_frames(t_win *win);
int		init_walltex(t_win *win);
void	free_frames(t_win *win);
void	handle_doors(t_win *win);
void	ft_recast_text(t_win *win, xpm_t **tex,
			double ray_Dirx, double ray_Diry);
void	ft_recast_ray(t_win *win, double ray_dirx, double ray_diry);
void	free_textures(t_win *win);
void	ft_recast_ray_helper(t_win *win, double ray_dirx, double ray_diry);
double	ft_recast_loop(t_win *win, int x);
void	ft_recast_loop_helper(t_win *win, int x, int check);
void	ft_movement_helper(t_win *win, int x, int y, int check);
void	ft_recto_helper(t_win *win, int x, int y, int color);
void	ft_draw_case(t_win *win, int x, int y);
void	init_window(t_win *win, t_wall *wall_dim);
void	free_window(t_win *win, t_garbage **garbage, int fd);

#endif