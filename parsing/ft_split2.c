/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:51:11 by tibarike          #+#    #+#             */
/*   Updated: 2025/08/24 15:28:43 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static	int	count_words(const char *s, char c)
{
	int	words;
	int	i;

	words = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			words++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (words);
}

static	char	*duplicate(const char *s, char c, t_garbage **garbage)
{
	int		i;
	char	*p;
	int		len;

	len = 0;
	i = 0;
	while (s[len] != c && s[len])
		len++;
	p = ft_malloc(len + 1, garbage);
	if (!p)
		return (NULL);
	while (i < len)
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	**ft_split2(char *s, char c, t_garbage **garbage)
{
	int		i;
	int		j;
	char	**res;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	res = ft_malloc(sizeof(char *) * (count_words(s, c) + 1), garbage);
	if (!res)
		return (NULL);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			res[j++] = duplicate(s + i, c, garbage);
			if (res[j - 1] == NULL)
				return (NULL);
		}
		while (s[i] && s[i] != c)
			i++;
	}
	return (res[j] = 0, res);
}
