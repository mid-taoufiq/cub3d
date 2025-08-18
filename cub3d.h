/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 11:35:29 by tibarike          #+#    #+#             */
/*   Updated: 2025/08/18 17:34:06 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "parsing/get_next_line.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>

char	**ft_split(char const *s, char c);

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