/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 11:35:29 by tibarike          #+#    #+#             */
/*   Updated: 2025/08/21 13:40:08 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_wall
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor[2];
	int		ceiling[2];
	int		no_filled;
	int		we_filled;
	int		ea_filled;
	int		so_filled;
	int		f_filled;
	int		c_filled;
}	t_wall;

char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(char *str);
char	*ft_strdup(char *str);
char	*ft_substr(char *s, unsigned int start, size_t len);
int		find_newline(char *str);
char	*get_next_line(int fd);
void	free_splits(char **split);
int		ft_atoi(const char *nb);
int		arg_counter(char **arr);
char	**ft_split(char const *s);
char	**ft_split2(char const *s, char c);
int		add_colors(t_wall *wall_dim, char *line);
int		check_empty_line(char *line);
void	free_struct(t_wall *wall_dim);
int		ft_strsearch(char *str, char *search);
int		arg_counter(char **arr);
int		add_dimensions2(t_wall *wall_dim, char *line);
int		add_dimensions(t_wall *wall_dim, char *line);

#endif