/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 15:10:48 by tibarike          #+#    #+#             */
/*   Updated: 2025/08/26 13:13:29 by tibarike         ###   ########.fr       */
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
	if (old_darray)
	{
		while (old_darray[i])
		{
			new_darray[i] = ft_strdup(old_darray[i], garbage);
			if (!new_darray[i])
				return (NULL);
			i++;
		}
	}
	new_darray[i] = ft_strdup(line, garbage);
	if (!new_darray[i])
		return (NULL);
	i++;
	new_darray[i] = NULL;
	return (new_darray);
}

int	add_to_map(char *line, t_wall *wall_dim, t_garbage **garbage, int fd)
{
	if (check_options(wall_dim, 0)
		&& (ft_strsearch(line, "1") || ft_strsearch(line, "0")))
	{
		while (line && !check_empty_line(line))
		{
			wall_dim->map = ft_darrayjoin(wall_dim->map, line, garbage);
			if (!wall_dim->map)
				return (0);
			line = get_next_line(fd);
		}
		wall_dim->map_filled = 1;
	}
	return (1);
}
