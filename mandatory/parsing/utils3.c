/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakroud <aakroud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:24:39 by tibarike          #+#    #+#             */
/*   Updated: 2025/10/06 17:13:22 by aakroud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_strncmp(char *str1, char *str2, int n)
{
	int	i;
	int	j;
	int	r;

	if (n == 0)
		return (0);
	j = 0;
	r = 0;
	while (str1[j] == ' ')
		j++;
	i = j;
	while ((str1[i] || str2[r]) && i < n + j)
	{
		if (str1[i] != str2[r])
			return (0);
		i++;
		r++;
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

char	*ft_strtrimlast(char *s1, char *set, t_garbage **garbage)
{
	int		start;
	char	*str;
	int		end;
	int		i;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (end > start && is_set(s1[end - 1], set))
		end--;
	str = ft_malloc(end + 1, garbage);
	if (!str)
		return (NULL);
	i = 0;
	while (start < end)
		str[i++] = s1[start++];
	str[i] = '\0';
	return (str);
}
