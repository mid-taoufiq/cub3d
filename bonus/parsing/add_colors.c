/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:01:06 by tibarike          #+#    #+#             */
/*   Updated: 2025/10/26 18:06:13 by tibarike         ###   ########.fr       */
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

static int	add_colors2(char *surface_split, int *surface, t_garbage **garbage)
{
	char	**color_split;
	int		i;

	color_split = NULL;
	i = 0;
	if (comma_counter(surface_split) != 2)
		return (write(2, "Error\ncolors error\n", 20), 0);
	color_split = ft_split(surface_split, ',', garbage);
	if (!color_split)
		return (0);
	if (arg_counter(color_split) != 3)
		return (write(2, "Error\ncolors error\n", 20), 0);
	while (i < 3)
	{
		surface[i] = ft_atoi(color_split[i]);
		if (surface[i] < 0 || surface[i] > 255)
			return (write(2, "Error\ncolors error\n", 20), 0);
		i++;
	}
	return (1);
}

static int	ceiling_part(t_wall *wall_dim, char *line, t_garbage **garbage)
{
	char	*surface_split;
	int		i;
	int		len;
	int		ceiling[3];

	i = ft_strncmp(line, "C ", 2);
	len = 0;
	while (line[len])
		len++;
	surface_split = NULL;
	if (i != 0)
	{
		if (wall_dim->c_filled)
			return (write (2, "Error\noption repeated\n", 23), 0);
		surface_split = ft_substr(line, i, len - 1, garbage);
		if (!surface_split)
			return (0);
		if (!add_colors2(surface_split, ceiling, garbage))
			return (0);
		wall_dim->ceiling = ft_color(ceiling[0], ceiling[1], ceiling[2], 255);
		wall_dim->c_filled = 1;
		return (2);
	}
	return (1);
}

int	add_colors(t_wall *wall_dim, char *line, t_garbage **garbage)
{
	char	*surface_split;
	int		i;
	int		len;
	int		floor[3];

	i = ft_strncmp(line, "F ", 2);
	len = 0;
	while (line[len])
		len++;
	surface_split = NULL;
	if (i != 0)
	{
		if (wall_dim->f_filled)
			return (write (2, "Error\noption repeated\n", 23), 0);
		surface_split = ft_substr(line, i, len - 1, garbage);
		if (!surface_split)
			return (0);
		if (!add_colors2(surface_split, floor, garbage))
			return (0);
		wall_dim->floor = ft_color(floor[0], floor[1], floor[2], 255);
		wall_dim->f_filled = 1;
		return (2);
	}
	return (ceiling_part(wall_dim, line, garbage));
}
