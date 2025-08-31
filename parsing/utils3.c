/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:24:39 by tibarike          #+#    #+#             */
/*   Updated: 2025/08/31 13:41:55 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_strncmp(char *str1, char *str2, size_t n)
{
	int	i;
	int	j;

	if (n == 0)
		return (0);
	i = 0;
	j = 0;
	while (str1[j] == ' ')
		j++;
	while ((str1[i] || str2[i]) && i < n + j)
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	return (i);
}

static int	is_set(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char *set, t_garbage **garbage)
{
	int		start;
	char	*str;
	int		end;
	int		i;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && is_set(s1[start], set))
		start++;
	while (end > start && is_set(s1[end - 1], set))
		end--;
	str = ft_malloc(end - start + 1, garbage);
	if (!str)
		return (NULL);
	i = 0;
	while (start < end)
		str[i++] = s1[start++];
	str[i] = '\0';
	return (str);
}
