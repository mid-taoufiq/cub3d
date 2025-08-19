/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:51:11 by tibarike          #+#    #+#             */
/*   Updated: 2025/08/19 11:07:27 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_whitespace(char c)
{
	if (c == ' ' || c == '\n')
		return (1);
	return (0);
}

static	int	count_words(const char *s)
{
	int	words;
	int	i;

	words = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && is_whitespace(s[i]))
			i++;
		if (s[i] && !is_whitespace(s[i]))
			words++;
		while (s[i] && !is_whitespace(s[i]))
			i++;
	}
	return (words);
}

static	char	*duplicate(const char *s)
{
	int		i;
	char	*p;
	int		len;

	len = 0;
	i = 0;
	while (s[len] && !is_whitespace(s[len]))
		len++;
	p = malloc(len + 1);
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

static	void	free_mem(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}

char	**ft_split(char const *s)
{
	int		i;
	int		j;
	char	**res;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	res = malloc(sizeof(char *) * (count_words(s) + 1));
	if (!res)
		return (NULL);
	while (s[i])
	{
		while (s[i] && is_whitespace(s[i]))
			i++;
		if (s[i] && !is_whitespace(s[i]))
		{
			res[j++] = duplicate(s + i);
			if (res[j - 1] == NULL)
				return (free_mem(res), NULL);
		}
		while (s[i] && !is_whitespace(s[i]))
			i++;
	}
	return (res[j] = 0, res);
}
