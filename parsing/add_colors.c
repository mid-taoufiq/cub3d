/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:01:06 by tibarike          #+#    #+#             */
/*   Updated: 2025/08/24 15:27:27 by tibarike         ###   ########.fr       */
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
		return (write(2, "wrong file arguments\n", 21), 0);
	color_split = ft_split2(surface_split, ',', garbage);
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

static int	ceiling_part(t_wall *wall_dim, char *line, t_garbage **garbage)
{
	char	*surface_split;
	int		i;
	int		len;

	(void)wall_dim;
	i = ft_strsearch(line, "C ");
	len = 0;
	while (line[len])
		len++;
	surface_split = NULL;
	if (i != 0)
	{
		surface_split = ft_substr(line, i, len, garbage);
		if (!surface_split)
			return (0);
		if (!add_colors2(surface_split, wall_dim->ceiling, garbage))
			return (0);
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

	(void)wall_dim;
	i = ft_strsearch(line, "F ");
	len = 0;
	while (line[len])
		len++;
	surface_split = NULL;
	if (i != 0)
	{
		surface_split = ft_substr(line, i, len, garbage);
		if (!surface_split)
			return (0);
		if (!add_colors2(surface_split, wall_dim->ceiling, garbage))
			return (0);
		wall_dim->f_filled = 1;
		return (2);
	}
	return (ceiling_part(wall_dim, line, garbage));
}
