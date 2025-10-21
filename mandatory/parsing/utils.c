/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakroud <aakroud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:32:50 by tibarike          #+#    #+#             */
/*   Updated: 2025/10/06 17:13:16 by aakroud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_strsearch2(char *str, char *search)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		j = 0;
		while (str[i + j] == search[j] && str[i + j])
			j++;
		if (search[j] == '\0')
			return (i + j);
		i++;
	}
	return (0);
}

int	ft_strsearch(char *str, char *search)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		j = 0;
		while (str[i + j] == search[j] && str[i + j])
			j++;
		if (search[j] == '\0')
			return (1);
		i++;
	}
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	check_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0')
		return (1);
	return (0);
}

int	ft_atoi(char *nb)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while ((nb[i] >= 9 && nb[i] <= 13) || nb[i] == 32)
		i++;
	if (nb[i] == '-' || nb[i] == '+')
	{
		if (nb[i] == '-')
			return (-1);
		i++;
	}
	while (nb[i] >= '0' && nb[i] <= '9')
	{
		result = (result * 10) + (nb[i] - '0');
		if (result > INT_MAX)
			return (-1);
		i++;
	}
	while (nb[i] == ' ')
		i++;
	if (nb[i])
		return (-1);
	return ((int)result);
}
