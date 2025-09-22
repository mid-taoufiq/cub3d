/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 11:40:58 by tibarike          #+#    #+#             */
/*   Updated: 2025/09/22 10:37:42 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_extansion(char *line, char *extansion)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	if (line[i - 1] != extansion[3] || line[i - 2] != extansion[2]
		|| line[i - 3] != extansion[1] || line[i - 4] != extansion[0])
		return (0);
	return (1);
}

void f()
{
    system("leaks cub3d");
}

int	main(int argc, char **argv)
{
	t_wall		wall_dim;
	int			fd;
	char		*line;
	t_garbage	*garbage;

    atexit(f);
	struct_init(&wall_dim);
	line = NULL;
	if (argc != 2 || !check_extansion(argv[1], ".cub"))
		return (write(2, "not valid arguments\n", 21), 1);
	garbage = NULL;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (perror(argv[1]), 1);
	if (!parsing(line, fd, &wall_dim, &garbage))
		return (close(fd), ft_lstclear(&garbage), 1);
	if (!check_remaining(fd, line, &wall_dim, &garbage))
		return (close(fd), ft_lstclear(&garbage), 1);
	if (!parse_map(&wall_dim, 0))
		return (close(fd), ft_lstclear(&garbage), 1);
	printf("%s\n", wall_dim.no);
	printf("%s\n", wall_dim.we);
	printf("%s\n", wall_dim.ea);
	printf("%s\n", wall_dim.so);
	printf("[%d]\n", wall_dim.ceiling);
	printf("[%d]\n", wall_dim.floor);
	for(int i = 0; wall_dim.map[i]; i++)
		printf("%s\n", wall_dim.map[i]);
	return (close(fd), ft_lstclear(&garbage), 0);
}
