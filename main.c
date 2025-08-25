/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 11:40:58 by tibarike          #+#    #+#             */
/*   Updated: 2025/08/25 13:10:26 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
			return (0);
		else if (return_value == 2)
			continue ;
		return_value = add_colors(wall_dim, line, garbage);
		if (!return_value)
			return (0);
		else if (return_value == 2)
			continue ;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_wall		wall_dim;
	int			fd;
	t_garbage	*garbage;

	struct_init(&wall_dim);
	if (argc != 2)
		return (1);
	garbage = NULL;
	fd = open(argv[1], O_RDONLY);
	if (!parsing(NULL, fd, &wall_dim, &garbage))
		return (close(fd), ft_lstclear(&garbage), 1);
	printf("[%d] ", wall_dim.ceiling[0]);
	printf("[%d] ", wall_dim.ceiling[1]);
	printf("[%d]\n", wall_dim.ceiling[2]);
	printf("[%d] ", wall_dim.floor[0]);
	printf("[%d] ", wall_dim.floor[1]);
	printf("[%d]\n", wall_dim.floor[2]);
	printf("%s\n", wall_dim.no);
	printf("%s\n", wall_dim.we);
	printf("%s\n", wall_dim.ea);
	printf("%s\n", wall_dim.so);
	printf("%s\n", wall_dim.map[0]);
	printf("%s\n", wall_dim.map[1]);
	printf("%s\n", wall_dim.map[2]);
	return (0);
}
