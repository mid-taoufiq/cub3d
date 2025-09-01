/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 11:35:29 by tibarike          #+#    #+#             */
/*   Updated: 2025/09/01 11:16:13 by tibarike         ###   ########.fr       */
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
	int		floor;
	int		ceiling;
	char	**map;
	int		no_filled;
	int		we_filled;
	int		ea_filled;
	int		so_filled;
	int		f_filled;
	int		c_filled;
	int		map_filled;
}	t_wall;

void	*ft_malloc(int size, t_garbage **garbage);
char	*ft_strjoin(char *s1, char *s2, t_garbage **garbage);
int		ft_strlen(char *str);
int		ft_strncmp(char *str1, char *str2, int n);
char	*ft_strdup(char *str, t_garbage **garbage);
char	*ft_substr(char *s, int start, int len, t_garbage **garbage);
char	*ft_strtrim(char *s1, char *set, t_garbage **garbage);
int		find_newline(char *str);
char	*get_next_line(int fd);
int		ft_atoi(char *nb);
int		arg_counter(char **arr);
char	**ft_split(char *s, t_garbage **garbage);
char	**ft_split2(char *s, char c, t_garbage **garbage);
int		add_colors(t_wall *wall_dim, char *line, t_garbage **garbage);
int		check_empty_line(char *line);
int		ft_strsearch(char *str, char *search);
int		ft_strsearch2(char *str, char *search);
int		arg_counter(char **arr);
int		add_dimensions(t_wall *wall_dim, char *line, t_garbage **garbage);
void	ft_lstclear(t_garbage **lst);
int		add_to_map(char *line, t_wall *wall_dim, t_garbage **garbage, int fd);
int		check_options(t_wall *wall, int option);
int		parse_map(char **map);
int		check_remaining(int fd, char *line);
void	struct_init(t_wall *wall_dim);
int		parsing(char *line, int fd, t_wall *wall_dim, t_garbage **garbage);
int		check_extansion(char *line, char *extansion);

#endif