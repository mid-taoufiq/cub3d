/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:11:37 by tibarike          #+#    #+#             */
/*   Updated: 2025/08/27 15:02:56 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	player_match(char c)
{
	if (c == 'N' || c == 'W' || c == 'E' || c == 'S')
		return (1);
	return (0);
}

int	parse_zero(char **map, int i, int j)
{
	if (i == 0 || j == 0)
		return (0);
	if (map[i - 1][j] != 1 || map[i - 1][j] != 0
		|| !player_match(map[i - 1][j]))
		return (0);
	if (map[i + 1][j] != 1 || map[i + 1][j] != 0
		|| !player_match(map[i + 1][j]))
		return (0);
	if (map[i][j - 1] != 1 || map[i][j - 1] != 0
		|| !player_match(map[i][j - 1]))
		return (0);
	if (map[i][j + 1] != 1 || map[i][j + 1] != 0
		|| !player_match(map[i][j + 1]))
		return (0);
}

int	parse_map(char **map)
{
	int	i;
	int	j;
	int	player_count;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
			{
				if (!parse_zero(map, i, j))
					return (write(2, "map not correct\n", 17), 0);
			}
			else if (player_match(map[i][j]))
				player_count++;
			else if (map[i][j] != '1')
				return (write(2, "map not correct\n", 17), 0);
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (write(2, "more than one player in map\n", 29), 0);
}
