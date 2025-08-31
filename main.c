/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 11:40:58 by tibarike          #+#    #+#             */
/*   Updated: 2025/08/31 12:44:32 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_extansion(char *line)
{
	int i;
	int count;
	int	j;

	j = 0;
	count = 0;
	while (line[j])
	{
		if (line[j++] == '.')
			count++;
	}
	if (count != 1)
		return (0);
	i = 0;
	while (line[i])
		i++;
	if (line[i - 1] != 'b' || line[i - 2] != 'u' || line[i - 3] != 'c'
		|| line[i - 4] != '.')
		return (0);
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
	if (argc != 2 || !check_extansion(argv[1]))
		return (write(2, "not valid arguments\n", 21), 1);
	garbage = NULL;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (perror(argv[1]), 1);
	if (!parsing(line, fd, &wall_dim, &garbage))
		return (close(fd), ft_lstclear(&garbage), 1);
	if (!check_remaining(fd, line))
		return (close(fd), ft_lstclear(&garbage), 1);
	if (!wall_dim.map || !parse_map(wall_dim.map))
		return (close(fd), ft_lstclear(&garbage), 1);
	printf("%s\n", wall_dim.no);
	printf("%s\n", wall_dim.we);
	printf("%s\n", wall_dim.ea);
	printf("%s\n", wall_dim.so);
	printf("[%d] ", wall_dim.ceiling[0]);
	printf("[%d] ", wall_dim.ceiling[1]);
	printf("[%d]\n", wall_dim.ceiling[2]);
	printf("[%d] ", wall_dim.floor[0]);
	printf("[%d] ", wall_dim.floor[1]);
	printf("[%d]\n", wall_dim.floor[2]);
	for(int i = 0; wall_dim.map[i]; i++)
		printf("%s\n", wall_dim.map[i]);
	return (0);
}
