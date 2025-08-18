/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 11:40:58 by tibarike          #+#    #+#             */
/*   Updated: 2025/08/18 18:30:00 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strsearch(char *str, char *search)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		j = 0;
		while (str[i + j] == search[j] && str[i + j])
			j++;
		if (search[j] == '\0')
			return (1);
		i++;
	}
	return (0);
}

int	arg_counter(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

char	*add_path(char *line)
{
	char	**arr;
	char	*path;
	int		i;

	arr = ft_split(line, ' ');
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

int	add_dimensions(t_wall *wall_dim, char *line)
{
	if (ft_strsearch(line, "NO"))
	{
		wall_dim->no = add_path(line);
		if (!wall_dim->no)
			return (0);
	}
	if (ft_strsearch(line, "WE"))
	{
		wall_dim->we = add_path(line);
		if (!wall_dim->we)
			return (0);
	}
	if (ft_strsearch(line, "EA"))
	{
		wall_dim->ea = add_path(line);
		if (!wall_dim->ea)
			return (0);
	}
	if (ft_strsearch(line, "SO"))
	{
		wall_dim->so = add_path(line);
		if (!wall_dim->so)
			return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	char	*line;
	int		fd;
	t_wall	wall_dim;

	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (!add_dimensions(&wall_dim, line))
			return (1);
		line = get_next_line(fd);
	}
	return (0);
}
