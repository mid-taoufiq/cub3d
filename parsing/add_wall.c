/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:00:54 by tibarike          #+#    #+#             */
/*   Updated: 2025/08/26 15:02:48 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	*add_path(char *line, t_garbage **garbage)
{
	char	**arr;
	char	*path;
	int		i;

	arr = ft_split(line, garbage);
	if (!arr)
		return (NULL);
	i = arg_counter(arr);
	if (i != 2)
		return (write(2, "texture file argument not correct\n", 35), NULL);
	path = ft_strdup(arr[1], garbage);
	i = 0;
	return (path);
}

int	add_dimensions2(t_wall *wall_dim, char *line, t_garbage **garbage)
{
	if (ft_strsearch(line, "EA ") != 0)
	{
		if (!wall_dim->ea_filled)
			wall_dim->ea = add_path(line, garbage);
		else
			return (write(2, "option repeated\n", 16), 0);
		if (!wall_dim->ea)
			return (0);
		wall_dim->ea_filled = 1;
		return (free(line), 2);
	}
	if (ft_strsearch(line, "SO ") != 0)
	{
		if (!wall_dim->so_filled)
			wall_dim->so = add_path(line, garbage);
		else
			return (write(2, "option repeated\n", 16), 0);
		if (!wall_dim->so)
			return (0);
		wall_dim->so_filled = 1;
		return (free(line), 2);
	}
	return (1);
}

int	add_dimensions(t_wall *wall_dim, char *line, t_garbage **garbage)
{
	if (ft_strsearch(line, "NO ") != 0)
	{
		if (!wall_dim->no_filled)
			wall_dim->no = add_path(line, garbage);
		else
			return (write(2, "option repeated\n", 16), 0);
		if (!wall_dim->no)
			return (0);
		wall_dim->no_filled = 1;
		return (free(line), 2);
	}
	if (ft_strsearch(line, "WE ") != 0)
	{
		if (!wall_dim->we_filled)
			wall_dim->we = add_path(line, garbage);
		else
			return (write(2, "option repeated\n", 16), 0);
		if (!wall_dim->we)
			return (0);
		wall_dim->we_filled = 1;
		return (free(line), 2);
	}
	return (add_dimensions2(wall_dim, line, garbage));
}
