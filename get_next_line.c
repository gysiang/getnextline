/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:30:47 by gyong-si          #+#    #+#             */
/*   Updated: 2023/10/19 16:56:12 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>

static char	*ft_free(char *s)
{
	if (s != NULL)
		free(s);
	return (NULL);
}

static char	*extract_line(char *buffer)
{
	char	*line;
	int		len;
	int		i;

	len = 0;
	i = 0;
	if (buffer == NULL || buffer[i] == '\0')
		return (NULL);
	while (buffer[len] != '\n')
		len++;
	line = (char *)malloc(sizeof(char) * (len + 2));
	if (!line)
		return (NULL);
	while (buffer[i] != '\n' && buffer[i] != '\0')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

static	char	*ft_nextchunk(char *buffer, size_t len)
{
	char	*result;
	int		i;
	size_t	buffer_len;
	size_t	len_to_copy;

	i = 0;
	buffer_len = ft_strlen(buffer);
	len_to_copy = buffer_len - len + 1;
	result = (char *)malloc(sizeof(char) * len_to_copy);
	if (!result)
		return (NULL);
	while (buffer[len + i] != '\0')
	{
		result[i] = buffer[len + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*read_file(int fd, char *text)
{
	char	*res;
	char	*tmp;
	ssize_t	bytes_read;

	res = (char *)malloc(BUFFER_SIZE + 1);
	if (res == NULL)
		return (ft_free(text));
	bytes_read = 1;
	while (1)
	{
		bytes_read = read(fd, res, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		res[bytes_read] = '\0';
		tmp = ft_strjoin(text, res);
		text = tmp;
	}
	free(res);
	return (text);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*line;

	if (BUFFER_SIZE < 1 || fd < 0 || fd > MAX_FILES_OPEN)
		return (NULL);
	if (!buffer)
	{
		buffer = (char *)malloc(sizeof(char) * 1);
		printf("Allocating buffer %p\n", (void *)buffer);
	}
	buffer = read_file(fd, buffer);
	line = extract_line(buffer);
	if (line == NULL)
	{
		printf("Freeing buffer: %p\n", (void *)buffer);
		free(buffer);
		buffer = NULL;
		return (ft_free(line));
	}
	buffer = ft_nextchunk(buffer, ft_strlen(line));
	return (line);
}

int	main(void)
{
	char	*line = NULL;
	int	fd;
	int	i = 0;

	fd = open("example.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			return (0);
		printf("LINE %d: %s",i++, line);	
	}
}
