/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 11:38:01 by tibarike          #+#    #+#             */
/*   Updated: 2025/08/24 15:28:58 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	find_newline(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strjoin(char *s1, char *s2, t_garbage **garbage)
{
	int		j;
	int		i;
	char	*str;

	if (!s1)
		return (ft_strdup(s2, garbage));
	if (!s2)
		return (ft_strdup(s1, garbage));
	str = ft_malloc(ft_strlen(s1) + ft_strlen(s2) + 1, garbage);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}

char	*ft_substr(char *s, int start, size_t len, t_garbage **garbage)
{
	char	*p;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	len = ft_strlen(s + start);
	p = ft_malloc(len + 1, garbage);
	if (!p)
		return (NULL);
	while (i < len)
	{
		p[i] = s[start];
		i++;
		start++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_strdup(char *str, t_garbage **garbage)
{
	int		i;
	char	*p;

	i = 0;
	while (str[i])
		i++;
	p = ft_malloc(i + 1, garbage);
	if (!p)
		return (NULL);
	i = 0;
	while (str[i])
	{
		p[i] = str[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
