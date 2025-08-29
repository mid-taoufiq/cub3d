/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 11:40:58 by tibarike          #+#    #+#             */
/*   Updated: 2025/08/29 14:44:04 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	if (!check_remaining(fd, line))
		return (close(fd), ft_lstclear(&garbage), 1);
	if (!parse_map(wall_dim.map))
		return (close(fd), ft_lstclear(&garbage), 1);
	return (0);
}
