/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 11:35:29 by tibarike          #+#    #+#             */
/*   Updated: 2025/08/19 15:32:13 by tibarike         ###   ########.fr       */
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
int		add_colors(int **surface, char *line);

typedef struct s_wall
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		*floor;
	int		*ceiling;
}	t_wall;

#endif