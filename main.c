/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 11:40:58 by tibarike          #+#    #+#             */
/*   Updated: 2025/08/21 14:53:06 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parsing(char *line, int fd, t_wall *wall_dim, int return_value)
{
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			return (1);
		if (check_empty_line(line))
			continue ;
		return_value = add_dimensions(&wall_dim, line);
		if (!return_value)
			return (0);
		else if (return_value == 2)
			continue ;
		return_value = add_colors(&wall_dim, line);
		if (!return_value)
			return (free_struct(&wall_dim), 0);
		else if (return_value == 2)
			continue ;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_wall	wall_dim;
	int		return_value;
	int		fd;

	if (argc != 2)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (!parsing(NULL, fd, &wall_dim, 0))
		return (1);
	return (0);
}
