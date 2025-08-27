/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 11:40:58 by tibarike          #+#    #+#             */
/*   Updated: 2025/08/26 17:59:11 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_remaining(t_wall *wall_dim, int fd, char *line)
{
	if (check_options(wall_dim, 1))
	{
		line = get_next_line(fd);
		while (line)
		{
			if (check_empty_line(line))
			{
				free(line);
				line = get_next_line(fd);
				continue ;
			}
			else
				return (write(2, "extra arguments in file\n", 25), 0);
			free(line);
			line = get_next_line(fd);
		}
	}
	else
		return (write(2, "missing arguments in file\n", 27), 0);
	return (1);
}

void	struct_init(t_wall *wall_dim)
{
	wall_dim->no = NULL;
	wall_dim->we = NULL;
	wall_dim->ea = NULL;
	wall_dim->so = NULL;
	wall_dim->map = NULL;
	wall_dim->no_filled = 0;
	wall_dim->we_filled = 0;
	wall_dim->ea_filled = 0;
	wall_dim->so_filled = 0;
	wall_dim->ceiling[0] = 0;
	wall_dim->ceiling[1] = 0;
	wall_dim->ceiling[2] = 0;
	wall_dim->floor[0] = 0;
	wall_dim->floor[1] = 0;
	wall_dim->floor[2] = 0;
}

int	parsing2(char *line, int fd, t_wall *wall_dim, t_garbage **garbage)
{
	int	return_value;

	if (!add_to_map(line, wall_dim, garbage, fd))
		return (free(line), 0);
	return_value = check_options(wall_dim, 1);
	if (return_value == 0)
		return (free(line), 0);
	return (free(line), 1);
}

int	parsing(char *line, int fd, t_wall *wall_dim, t_garbage **garbage)
{
	int	return_value;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			return (1);
		if (check_empty_line(line))
			continue ;
		return_value = add_dimensions(wall_dim, line, garbage);
		if (!return_value)
			return (free(line), 0);
		else if (return_value == 2)
			continue ;
		return_value = add_colors(wall_dim, line, garbage);
		if (!return_value)
			return (free(line), 0);
		else if (return_value == 2)
			continue ;
		if (!parsing2(line, fd, wall_dim, garbage))
			return (0);
		else
			return (1);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_wall		wall_dim;
	int			fd;
	char		*line;
	t_garbage	*garbage;

	struct_init(&wall_dim);
	line = NULL;
	if (argc != 2)
		return (1);
	garbage = NULL;
	fd = open(argv[1], O_RDONLY);
	if (!parsing(line, fd, &wall_dim, &garbage))
		return (close(fd), ft_lstclear(&garbage), 1);
	if (!check_remaining(&wall_dim, fd, line))
		return (close(fd), ft_lstclear(&garbage), 1);
	return (0);
}
