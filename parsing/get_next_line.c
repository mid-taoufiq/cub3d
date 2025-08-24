/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 11:37:59 by tibarike          #+#    #+#             */
/*   Updated: 2025/08/24 15:33:49 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	*extract_line(char **buffer, t_garbage **garbage, int index)
{
	char	*line;
	char	*tmp;

	if (!(*buffer) || **buffer == '\0')
		return (NULL);
	index = find_newline(*buffer);
	if (index >= 0)
	{
		line = ft_substr(*buffer, 0, index + 1, garbage);
		tmp = ft_substr(*buffer, index + 1,
				ft_strlen(*buffer) - index - 1, garbage);
		if (!line || !tmp)
			return (NULL);
		*buffer = tmp;
	}
	else
	{
		line = ft_substr(*buffer, 0, ft_strlen(*buffer), garbage);
		*buffer = NULL;
		if (!line)
			return (NULL);
	}
	return (line);
}

static char	*read_buff(int fd, char *buff, ssize_t read_b, t_garbage **garbage)
{
	char	*arr;
	char	*temp;

	arr = ft_malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char), garbage);
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
		temp = ft_strjoin(buff, arr, garbage);
		if (!temp)
			return (NULL);
		buff = temp;
	}
	if (!buff || *buff == '\0')
		return (NULL);
	return (buff);
}

char	*get_next_line(int fd, t_garbage **garbage)
{
	static char	*buffer;
	ssize_t		read_bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_bytes = 0;
	buffer = read_buff(fd, buffer, read_bytes, garbage);
	return (extract_line(&buffer, garbage, 0));
}
