/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 11:37:59 by tibarike          #+#    #+#             */
/*   Updated: 2025/09/22 10:29:38 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

static char	*extract_line(char **buffer, t_garbage **garb)
{
	char	*line;
	char	*tmp;
	int		index;

	if (!(*buffer) || **buffer == '\0')
		return (NULL);
	index = find_newline(*buffer);
	if (index >= 0)
	{
		line = ft_substr(*buffer, 0, index, garb);
		tmp = ft_substr(*buffer, index + 1, ft_strlen(*buffer) - index - 1,
				garb);
		if (!line || !tmp)
			return (NULL);
		*buffer = tmp;
	}
	else
	{
		line = ft_substr(*buffer, 0, ft_strlen(*buffer), garb);
		*buffer = NULL;
		if (!line)
			return (NULL);
	}
	return (line);
}

static	char	*read_buffer(int fd, char *buff, char *temp, t_garbage **garb)
{
	char	*arr;
	ssize_t	read_b;

	read_b = 0;
	arr = ft_malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char), garb);
	if (!arr)
		return (NULL);
	while (find_newline(buff) == -1)
	{
		read_b = read(fd, arr, BUFFER_SIZE);
		if (read_b == -1)
			return (NULL);
		if (read_b == 0)
			break ;
		arr[read_b] = '\0';
		temp = ft_strjoin(buff, arr, garb);
		if (!temp)
			return (NULL);
		buff = temp;
	}
	if (!buff || *buff == '\0')
		return (NULL);
	return (buff);
}

char	*get_next_line(int fd, t_garbage **garb)
{
	static char	*buffer;
	char		*temporary;
	ssize_t		read_bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_bytes = 0;
	temporary = NULL;
	buffer = read_buffer(fd, buffer, temporary, garb);
	return (extract_line(&buffer, garb));
}
