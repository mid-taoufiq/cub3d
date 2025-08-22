/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:10:25 by tibarike          #+#    #+#             */
/*   Updated: 2025/08/22 16:43:41 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

int	arg_counter(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}
