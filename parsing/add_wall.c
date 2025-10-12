/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:00:54 by tibarike          #+#    #+#             */
/*   Updated: 2025/10/07 16:35:19 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	*add_path(char *line, t_garbage **garbage, char *option)
{
	char	*tmp;
	char	*path;
	int		i;
	// int		fd;

	i = ft_strsearch2(line, option);
	tmp = ft_substr(line, i, ft_strlen(line), garbage);
	if (!tmp)
		return (NULL);
	path = ft_strtrim(tmp, " ", garbage);
	if (!path)
		return (NULL);
	if (path[0] == '\0' || !check_extansion(path, ".xpm"))
		return (write(2, "arguments error\n", 16), NULL);
	// fd = open(path, O_RDONLY);
	// if (fd < 0)
	// 	return (close(fd), write(2, "arguments error\n", 16), NULL);
	// close(fd);
	return (path);
}

int	add_dimensions2(t_wall *wall_dim, char *line, t_garbage **garbage)
{
	if (ft_strncmp(line, "EA ", 3) != 0)
	{
		if (wall_dim->ea_filled)
			return (write(2, "option repeated\n", 16), 0);
		wall_dim->ea = add_path(line, garbage, "EA ");
		if (!wall_dim->ea)
			return (0);
		wall_dim->ea_filled = 1;
		return (2);
	}
	if (ft_strncmp(line, "SO ", 3) != 0)
	{
		if (wall_dim->so_filled)
			return (write(2, "option repeated\n", 16), 0);
		wall_dim->so = add_path(line, garbage, "SO ");
		if (!wall_dim->so)
			return (0);
		wall_dim->so_filled = 1;
		return (2);
	}
	return (1);
}

int	add_dimensions(t_wall *wall_dim, char *line, t_garbage **garbage)
{
	if (ft_strncmp(line, "NO ", 3) != 0)
	{
		if (wall_dim->no_filled)
			return (write(2, "option repeated\n", 16), 0);
		wall_dim->no = add_path(line, garbage, "NO ");
		if (!wall_dim->no)
			return (0);
		wall_dim->no_filled = 1;
		return (2);
	}
	if (ft_strncmp(line, "WE ", 3) != 0)
	{
		if (wall_dim->we_filled)
			return (write(2, "option repeated\n", 16), 0);
		wall_dim->we = add_path(line, garbage, "WE ");
		if (!wall_dim->we)
			return (0);
		wall_dim->we_filled = 1;
		return (2);
	}
	return (add_dimensions2(wall_dim, line, garbage));
}
