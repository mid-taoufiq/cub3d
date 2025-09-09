/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakroud <aakroud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 11:35:29 by tibarike          #+#    #+#             */
/*   Updated: 2025/09/09 12:05:43 by aakroud          ###   ########.fr       */
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
# include "MLX42.h"
# include <math.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_garbage
{
	void				*address;
	struct s_garbage	*next;
}	t_garbage;

typedef struct s_wall
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor[3];
	int		ceiling[3];
	char	**map;
	int		no_filled;
	int		we_filled;
	int		ea_filled;
	int		so_filled;
	int		f_filled;
	int		c_filled;
}	t_wall;

typedef struct s_win
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	mlx_image_t	*img_player;
	int			tile;
	int			width;
	int			height;
	char		**arr;
	double			player_x;
	double			player_y;
	double		player_dirx;
	double		player_diry;
	double		plane_dirx;
	double		plane_diry;
	double		start_posx;
	double		start_posy;
}	t_win;

void	*ft_malloc(int size, t_garbage **garbage);
char	*ft_strjoin(char *s1, char *s2, t_garbage **garbage);
size_t	ft_strlen(char *str);
char	*ft_strdup(char *str, t_garbage **garbage);
char	*ft_substr(char *s, int start, size_t len, t_garbage **garbage);
int		find_newline(char *str);
char	*get_next_line(int fd, t_garbage **garbage);
int		ft_atoi(char *nb);
int		arg_counter(char **arr);
char	**ft_split(char *s, t_garbage **garbage);
char	**ft_split2(char *s, char c, t_garbage **garbage);
int		add_colors(t_wall *wall_dim, char *line, t_garbage **garbage);
int		check_empty_line(char *line);
int		ft_strsearch(char *str, char *search);
int		arg_counter(char **arr);
int		add_dimensions(t_wall *wall_dim, char *line, t_garbage **garbage);
void	ft_lstclear(t_garbage **lst);
int		ft_check_player(char c);
void	ft_draw_line(char c, t_win *win, int i, int j);

#endif