/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:00:54 by tibarike          #+#    #+#             */
/*   Updated: 2025/08/21 13:05:16 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	*add_path(char *line)
{
	char	**arr;
	char	*path;
	int		i;

	arr = ft_split(line);
	if (!arr)
		return (NULL);
	i = arg_counter(arr);
	if (i != 2)
		return (write(2, "wrong file arguments\n", 21), NULL);
	path = ft_strdup(arr[1]);
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (path);
}

int	add_dimensions2(t_wall *wall_dim, char *line)
{
	if (ft_strsearch(line, "EA "))
	{
		if (!wall_dim->ea)
			wall_dim->ea = add_path(line);
		else
			return (free_struct(wall_dim),
				write(2, "option repeated\n", 16), 0);
		if (!wall_dim->ea)
			return (free_struct(wall_dim), 0);
		wall_dim->ea_filled = 1;
		return (2);
	}
	if (ft_strsearch(line, "SO "))
	{
		if (!wall_dim->so)
			wall_dim->so = add_path(line);
		else
			return (free_struct(wall_dim),
				write(2, "option repeated\n", 16), 0);
		if (!wall_dim->so)
			return (free_struct(wall_dim), 0);
		wall_dim->so_filled = 1;
		return (2);
	}
	return (1);
}

int	add_dimensions(t_wall *wall_dim, char *line)
{
	if (ft_strsearch(line, "NO "))
	{
		if (!wall_dim->no)
			wall_dim->no = add_path(line);
		else
			return (free_struct(wall_dim),
				write(2, "option repeated\n", 16), 0);
		if (!wall_dim->no)
			return (free_struct(wall_dim), 0);
		wall_dim->no_filled = 1;
		return (2);
	}
	if (ft_strsearch(line, "WE "))
	{
		if (!wall_dim->we)
			wall_dim->we = add_path(line);
		else
			return (free_struct(wall_dim),
				write(2, "option repeated\n", 16), 0);
		if (!wall_dim->we)
			return (free_struct(wall_dim), 0);
		wall_dim->we_filled = 1;
		return (2);
	}
	return (add_dimensions2(wall_dim, line));
}
