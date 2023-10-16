/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:30:47 by gyong-si          #+#    #+#             */
/*   Updated: 2023/10/16 16:02:37 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_free(char *s1, char *s2)
{
	char	*tmp;
	
	tmp = ft_strjoin(s1, s2);
	free(s1);
	return (tmp);
}

static char	*get_line(char *s)
{
	char	*line;
	int		i;

	i = 0;
	if (!s[i])
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		line[i] = s[i];
		i++;
	}
	line[i] = '\n';
	return (line);
}
 
static char	*read_file(int fd, char *buf)
{
	char	*res;
	ssize_t		bytes_read;

	// assign memory to buffer based on buffersize
	res = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!res)
		return (NULL);
	bytes_read = 1;
	// this reads the file into the buffer
	while (bytes_read > 0)
	{
		//call the read function
		bytes_read = read(fd, res, BUFFER_SIZE);
		// case in which file read failed
		if (bytes_read <= 0)
		{
			free(res);
			return (NULL);
		}
		// add in 0 at the end to mark end of file
		res[bytes_read] = 0;
		// this will keep track of all the characters read
		buf = ft_free(buf, res);
		// if res == '\n', break the loop
		if (ft_strchr(res, '\n'))
			break ;
	}
	free(res);
	return (res);
}

static char	*ft_next(char *s)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (!s[i])
	{
		free(s);
		return (NULL);
	}
	res = (char *)malloc(sizeof(char) * ft_strlen(s) - i + 1);
	i++;
	j = 0;
	while (s[i])
		res[j++] = s[i++];
	free(s);
	return (res);
}

char	*get_next_line(int fd)
{
	static	char	*buffer;
	char	*line;

	// error handing
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = get_line(buffer);
	buffer = ft_next(buffer);
	return (line);
}

int	main(void)
{
	char	*line;
	int	fd;
	int	i;

	fd = open("example.txt", O_RDONLY);
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			return (0);
		printf("LINE %d: %s", i++, line);
	}
}
