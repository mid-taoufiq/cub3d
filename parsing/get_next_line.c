/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 11:37:59 by tibarike          #+#    #+#             */
/*   Updated: 2025/08/19 15:31:56 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

static char	*free_buffer(char **buffer)
{
	if (buffer && *buffer)
	{
		free (*buffer);
		*buffer = NULL;
	}
	return (NULL);
}

static char	*extract_line(char **buffer)
{
	char	*line;
	char	*tmp;
	int		index;

	if (!(*buffer) || **buffer == '\0')
		return (NULL);
	index = find_newline(*buffer);
	if (index >= 0)
	{
		line = ft_substr(*buffer, 0, index + 1);
		tmp = ft_substr(*buffer, index + 1, ft_strlen(*buffer) - index - 1);
		if (!line || !tmp)
			return (free(line), free(tmp), free_buffer(buffer));
		free(*buffer);
		*buffer = tmp;
	}
	else
	{
		line = ft_substr(*buffer, 0, ft_strlen(*buffer));
		free(*buffer);
		*buffer = NULL;
		if (!line)
			return (NULL);
	}
	return (line);
}

static	char	*read_buffer(int fd, char *buff, ssize_t read_b, char *temp)
{
	char	*arr;

	arr = malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (!arr)
		return (NULL);
	while (find_newline(buff) == -1)
	{
		read_b = read(fd, arr, BUFFER_SIZE);
		if (read_b == -1)
			return (free(arr), free_buffer(&buff));
		if (read_b == 0)
			break ;
		arr[read_b] = '\0';
		temp = ft_strjoin(buff, arr);
		if (!temp)
			return (free(arr), free_buffer(&buff));
		buff = temp;
	}
	free(arr);
	if (!buff || *buff == '\0')
		return (free_buffer(&buff));
	return (buff);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*temporary;
	ssize_t		read_bytes;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_bytes = 0;
	temporary = NULL;
	buffer = read_buffer(fd, buffer, read_bytes, temporary);
	return (extract_line(&buffer));
}
