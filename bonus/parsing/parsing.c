/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 13:37:44 by tibarike          #+#    #+#             */
/*   Updated: 2025/10/25 17:29:31 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_remaining(int fd, char *line, t_wall *wall, t_garbage **garbage)
{
	if (!check_options(wall, 1))
		return (write(2, "Error\narguments error\n", 23), 0);
	line = get_next_line(fd, garbage);
	while (line)
	{
		if (check_empty_line(line))
		{
			line = get_next_line(fd, garbage);
			continue ;
		}
		else
			return (write(2, "Error\narguments error\n", 23), 0);
		free(line);
		line = get_next_line(fd, garbage);
	}
	return (1);
}

int	struct_init(t_wall *wall_dim)
{
	wall_dim->no = NULL;
	wall_dim->we = NULL;
	wall_dim->ea = NULL;
	wall_dim->so = NULL;
	wall_dim->map = NULL;
	wall_dim->player_direction = 0;
	wall_dim->ceiling = 0;
	wall_dim->floor = 0;
	wall_dim->no_filled = 0;
	wall_dim->we_filled = 0;
	wall_dim->ea_filled = 0;
	wall_dim->so_filled = 0;
	wall_dim->c_filled = 0;
	wall_dim->f_filled = 0;
	wall_dim->map_filled = 0;
}

int	parsing2(char *line, int fd, t_wall *wall_dim, t_garbage **garbage)
{
	int	return_value;

	if (!add_to_map(line, wall_dim, garbage, fd))
		return (write(2, "Error\narguments error\n", 23), 0);
	return_value = check_options(wall_dim, 1);
	if (return_value == 0)
		return (write(2, "Error\narguments error\n", 23), 0);
	return (1);
}

int	parsing(char *line, int fd, t_wall *wall_dim, t_garbage **garbage)
{
	int	return_value;

	while (1)
	{
		line = get_next_line(fd, garbage);
		if (!line)
			return (1);
		if (check_empty_line(line))
			continue ;
		return_value = add_dimensions(wall_dim, line, garbage);
		if (!return_value)
			return (0);
		else if (return_value == 2)
			continue ;
		return_value = add_colors(wall_dim, line, garbage);
		if (!return_value)
			return (0);
		else if (return_value == 2)
			continue ;
		if (!parsing2(line, fd, wall_dim, garbage))
			return (0);
		else
			return (1);
	}
	return (1);
}
