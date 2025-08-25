/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 15:10:48 by tibarike          #+#    #+#             */
/*   Updated: 2025/08/25 17:33:48 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	**ft_darrayjoin(char **old_darray, char *line, t_garbage **garbage)
{
	int		i;
	char	**new_darray;

	i = arg_counter(old_darray);
	new_darray = ft_malloc(sizeof(char *) * (i + 2), garbage);
	i = 0;
	while (old_darray[i])
	{
		new_darray[i] = ft_strdup(old_darray[i], garbage);
		i++;
	}
	new_darray[i] = ft_strdup(line, garbage);
	i++;
	new_darray[i] = NULL;
	return (new_darray);
}

int	check_options(t_wall *wall)
{
	if (!wall->no_filled || !wall->we_filled || !wall->ea_filled
		|| !wall->so_filled || !wall->f_filled || !wall->c_filled)
		return (0);
	return (1);
}

int	parse_map(char *line, t_wall *wall_dim, t_garbage **garbage, int fd)
{
	if (check_options(wall_dim)
		&& (ft_strsearch("1", line) || ft_strsearch("0", line)))
	{
		while (!check_empty_line(line))
		{
			wall_dim->map = ft_darrayjoin(wall_dim->map, line, garbage);
			get_next_line(fd);
		}
	}
	return (1);
}
