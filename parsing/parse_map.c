/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 15:10:48 by tibarike          #+#    #+#             */
/*   Updated: 2025/08/22 13:16:46 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_options(t_wall *wall)
{
	if (!wall->no_filled || !wall->we_filled || !wall->ea_filled
		|| !wall->so_filled || !wall->f_filled || !wall->c_filled)
		return (0);
	return (1);
}

int	parse_map(char *line, t_wall*wall)
{
	if (check_options(wall)
		&& (ft_strsearch("1", line) || ft_strsearch("0", line)))
	{
		while (!check_empty_line(line))
		{
			
		}
	}
}