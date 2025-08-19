/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:32:50 by tibarike          #+#    #+#             */
/*   Updated: 2025/08/19 12:18:04 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_splits(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

static int	get_signal(const char *nb, int *index)
{
	int	signal;

	signal = 1;
	if (nb[*index] == '-' || nb[*index] == '+')
	{
		if (nb[*index] == '-')
			signal *= -1;
		(*index)++;
	}
	return (signal);
}

int	ft_atoi(const char *nb)
{
	int		i;
	long	result;
	int		signal;
	long	check;

	i = 0;
	result = 0;
	while ((nb[i] >= 9 && nb[i] <= 13) || nb[i] == 32)
		i++;
	signal = get_signal(nb, &i);
	while (nb[i] >= '0' && nb[i] <= '9')
	{
		check = result;
		result = (result * 10);
		result += (nb[i++] - '0');
		if (result / 10 != check)
		{
			if (signal == 1)
				return (-1);
			else
				return (0);
		}
	}
	return (result * signal);
}
