/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:11:37 by tibarike          #+#    #+#             */
/*   Updated: 2025/10/25 17:26:36 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	player_match(char c)
{
	if (c == 'N' || c == 'W' || c == 'E' || c == 'S')
		return (1);
	return (0);
}

int	is_valid(char c)
{
	return (c == '0' || c == '1' || player_match(c));
}

int	parse_palyer_0(char **map, int i, int j)
{
	if (i == 0 || j >= ft_strlen(map[i - 1]) || !is_valid(map[i - 1][j]))
		return (0);
	if (!map[i + 1] || j >= ft_strlen(map[i + 1]) || !is_valid(map[i + 1][j]))
		return (0);
	if (j == 0 || !is_valid(map[i][j - 1]))
		return (0);
	if (j + 1 >= ft_strlen(map[i]) || !is_valid(map[i][j + 1]))
		return (0);
	return (1);
}

int	handle_p(t_wall *wall, int i, int j, int *cplayer)
{
	(*cplayer)++;
	wall->player_direction = wall->map[i][j];
	if (!parse_palyer_0(wall->map, i, j))
		return (0);
	return (1);
}

int	parse_map(t_wall *wall, int cplayer)
{
	int	i;
	int	j;

	i = 0;
	while (wall->map[i])
	{
		j = 0;
		while (wall->map[i][j])
		{
			if (wall->map[i][j] == '0' && !parse_palyer_0(wall->map, i, j))
				return (write(2, "Error\nzero position not correct\n", 33), 0);
			else if (player_match(wall->map[i][j])
				&& !handle_p(wall, i, j, &cplayer))
				return (write(2, "Error\nplayer position not correct\n", 35), 0);
			else if (wall->map[i][j] != '1' && wall->map[i][j] != ' '
				&& wall->map[i][j] != '0' && wall->map[i][j] != 'D'
				&& !player_match(wall->map[i][j]))
				return (write(2, "Error\nunallowed character\n", 27), 0);
			j++;
		}
		i++;
	}
	if (cplayer != 1)
		return (write(2, "Error\nplayer not correct\n", 26), 0);
	return (1);
}
