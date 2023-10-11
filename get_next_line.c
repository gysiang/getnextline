/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 12:53:43 by gyong-si          #+#    #+#             */
/*   Updated: 2023/10/11 18:47:35 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

static	char	*ft_free(char *s)
{
	if (s != NULL)
		free(s);
	return (NULL);
}

static char	*read_line(int fd, char *text, size_t buf_size)
{
	char	*buffer;
	char	*tmp;
	ssize_t	bytesread;

	buffer = (char *)malloc(buf_size + 1);
	if (!buffer)
		return (ft_free(text));
	bytesread = 0;
	while (ft_strchr(text, '\n') == NULL)
	{
		bytesread = read(fd, buffer, buf_size);
		if (bytesread < 0)
			break;
		buffer[bytesread] = 0;
		tmp = ft_strjoin(text, buffer);
		free(text);
		text = tmp;
	}
	free(buffer);
	if (bytesread < 0)
		read(ft_free(text));
	return (text);
}

static char	*get_line(char *text)
{
	char	*location;

	location = ft_strchr(text, '\n');
	if (location == NULL)
		return (ft_strdup(text));
	return (ft_substr(text, 0, location - text + 1);
}

static	char	*front_trunc(char *text, size_t n)
{
	char	*out;

	if (text == NULL)
		return (NULL);
	if (n <= 0)
		return (text);
	if (n >= ft_strlen(text))
		return (ft_free(text));
	out = ft_strdup(&text[n]);
	free(text);
	return (out);
}

char	*get_next_line(int fd)
{
	static char	*text[10] = {0};
	char	*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	text[fd] = read_file(fd, text[fd], BUFFER_SIZE);
	line = get_line(text[fd]);
	text[fd] = front_trunc(text[fd], ft_strlen(line));
	return (line);
}
