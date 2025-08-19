/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:01:06 by tibarike          #+#    #+#             */
/*   Updated: 2025/08/19 14:03:14 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	add_colors2(char **surface_split, int **surface)
{
	char	**color_split;
	int		i;

	color_split = NULL;
	color_split = ft_split2(surface_split[1], ',');
	if (!color_split)
		return (0);
	i = arg_counter(color_split);
	if (i != 3)
		return (free_splits(surface_split), free_splits(color_split),
			write(2, "wrong file arguments\n", 21), 0);
	i = 0;
	while (i < 3)
	{
		*surface[i] = ft_atoi(color_split[i]);
		i++;
	}
	return (1);
}

int	add_colors(int **surface, char *line)
{
	char	**surface_split;
	int		i;

	surface_split = NULL;
	i = 0;
	if (ft_strsearch(line, "F"))
	{
		*surface = malloc(sizeof(int *) * 3);
		if (!*surface)
			return (0);
		surface_split = ft_split(line);
		if (!surface_split)
			return (0);
		i = arg_counter(surface_split);
		if (i != 2)
			return (free_splits(surface_split),
				write(2, "wrong file arguments\n", 21), 0);
		if (!add_colors2(surface_split, surface))
			return (0);
	}
	return (1);
}
