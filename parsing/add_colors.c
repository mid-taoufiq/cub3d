/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:01:06 by tibarike          #+#    #+#             */
/*   Updated: 2025/08/22 16:54:49 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	comma_counter(char *str)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == ',')
			counter++;
		i++;
	}
	return (counter);
}

static int	add_colors2(char **surface_split, int *surface, t_garbage *garbage)
{
	char	**color_split;
	int		i;

	color_split = NULL;
	i = 0;
	if (comma_counter(surface_split[1]) != 2)
		return (write(2, "wrong file arguments\n", 21), 0);
	color_split = ft_split2(surface_split[1], ',', garbage);
	if (!color_split)
		return (0);
	if (arg_counter(color_split) != 3)
		return (write(2, "wrong file arguments\n", 21), 0);
	while (i < 3)
	{
		surface[i] = ft_atoi(color_split[i]);
		if (surface[i] < 0 || surface[i] > 255)
			return (write(2, "wrong file arguments\n", 21), 0);
		i++;
	}
	return (1);
}

static int	ceiling_part(t_wall *wall_dim, char *line, t_garbage *garbage)
{
	char	**surface_split;

	surface_split = NULL;
	if (ft_strsearch(line, "C "))
	{
		surface_split = ft_split(line, garbage);
		if (!surface_split)
			return (0);
		if (arg_counter(surface_split) != 2)
			return (free_splits(surface_split),
				write(2, "wrong file arguments\n", 21), 0);
		if (!add_colors2(surface_split, wall_dim->ceiling, garbage))
			return (0);
		wall_dim->f_filled = 1;
		return (free(line), 2);
	}
	return (1);
}

int	add_colors(t_wall *wall_dim, char *line, t_garbage *garbage)
{
	char	**surface_split;

	surface_split = NULL;
	if (ft_strsearch(line, "F "))
	{
		surface_split = ft_split(line, garbage);
		if (!surface_split)
			return (0);
		if (arg_counter(surface_split) != 2)
			return (free_splits(surface_split),
				write(2, "wrong file arguments\n", 21), 0);
		if (!add_colors2(surface_split, wall_dim->floor, garbage))
			return (0);
		wall_dim->f_filled = 1;
		return (free(line), 2);
	}
	return (ceiling_part(wall_dim, line, garbage));
}
