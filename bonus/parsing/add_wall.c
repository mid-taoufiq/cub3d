/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:00:54 by tibarike          #+#    #+#             */
/*   Updated: 2025/11/15 14:12:23 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	*add_path(char *line, t_garbage **garbage, char *option)
{
	char	*tmp;
	char	*path;
	int		i;
	int		fd;

	i = ft_strsearch2(line, option);
	tmp = ft_substr(line, i, ft_strlen(line), garbage);
	if (!tmp)
		return (NULL);
	path = ft_strtrim(tmp, " ", garbage);
	if (!path)
		return (NULL);
	if (path[0] == '\0' || !check_extansion(path, ".xpm42", 1))
		return (write(2, "Error\narguments error\n", 23), NULL);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (close(fd), write(2, "Error\narguments error\n", 23), NULL);
	close(fd);
	return (path);
}

static int	add_door(char *line, t_wall *wall_dim, t_garbage **garbage)
{
	if (ft_strncmp(line, "D ", 2) != 0)
	{
		if (wall_dim->door_filled)
			return (write(2, "Error\noption repeated\n", 23), 0);
		wall_dim->d = add_path(line, garbage, "D ");
		if (!wall_dim->d)
			return (0);
		wall_dim->door_filled = 1;
		return (2);
	}
	return (1);
}

static int	add_dimensions2(t_wall *wall_dim, char *line, t_garbage **garbage)
{
	if (ft_strncmp(line, "EA ", 3) != 0)
	{
		if (wall_dim->ea_filled)
			return (write(2, "Error\noption repeated\n", 23), 0);
		wall_dim->ea = add_path(line, garbage, "EA ");
		if (!wall_dim->ea)
			return (0);
		wall_dim->ea_filled = 1;
		return (2);
	}
	if (ft_strncmp(line, "SO ", 3) != 0)
	{
		if (wall_dim->so_filled)
			return (write(2, "Error\noption repeated\n", 23), 0);
		wall_dim->so = add_path(line, garbage, "SO ");
		if (!wall_dim->so)
			return (0);
		wall_dim->so_filled = 1;
		return (2);
	}
	return (add_door(line, wall_dim, garbage));
}

int	add_dimensions(t_wall *wall_dim, char *line, t_garbage **garbage)
{
	if (ft_strncmp(line, "NO ", 3) != 0)
	{
		if (wall_dim->no_filled)
			return (write(2, "Error\noption repeated\n", 23), 0);
		wall_dim->no = add_path(line, garbage, "NO ");
		if (!wall_dim->no)
			return (0);
		wall_dim->no_filled = 1;
		return (2);
	}
	if (ft_strncmp(line, "WE ", 3) != 0)
	{
		if (wall_dim->we_filled)
			return (write(2, "Error\noption repeated\n", 23), 0);
		wall_dim->we = add_path(line, garbage, "WE ");
		if (!wall_dim->we)
			return (0);
		wall_dim->we_filled = 1;
		return (2);
	}
	return (add_dimensions2(wall_dim, line, garbage));
}
