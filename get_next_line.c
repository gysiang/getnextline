/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:30:47 by gyong-si          #+#    #+#             */
/*   Updated: 2023/10/18 18:13:02 by gyong-si         ###   ########.fr       */
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

	if (buffer == NULL || *buffer == '\0')
		return (NULL);
	// i think i have to allocate memory space for this based on length of line
	// find a way to calculate len up and including to the next '\n'
	len = 0;
	i = 0;
	while (buffer[i] != '\n')
	{
		i++;
		len++;
	}
	// now i have the length of the line
	line = (char *)malloc(sizeof(char) * (len + 2));
	if (!line)
		return (NULL);
	// do a loop to copy from buffer into line
	i = 0;
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
	// this should copy and return the line including '\n'
	return (line);
}

static	char	*ft_nextchunk(char *buffer, size_t len)
{
	char	*result;
	int		i;
	size_t		buffer_len;
	size_t		len_to_copy;
	
	i = 0;
	buffer_len = ft_strlen(buffer);
	len_to_copy = buffer_len - len + 1;
	result = (char *)malloc(sizeof(char) * len_to_copy);
	while (buffer[len + i] != '\0')
	{
		result[i] = buffer[len + i];
		i++;
	}
	// after copying no need for buffer anymore, free it.
	ft_free(buffer);
	result[i] = '\0';
	return (result);
}

char	*read_file(int fd, char *text) 
{
	char	*res;
	char	*tmp;
	ssize_t		bytes_read;

	res = (char *)malloc(BUFFER_SIZE + 1);
    	if (res == NULL)
        	return (ft_free(text));
	bytes_read = 1;
    	while (1) 
	{
        	bytes_read = read(fd, res, BUFFER_SIZE);
        	if (bytes_read <= 0)
            		break;
        	res[bytes_read] = '\0';
        	tmp = ft_strjoin(text, res);
        	text = tmp;
    	}
    	free(res);
    	return (text);
}


char	*get_next_line(int fd)
{
	static	char	*buffer;
	char	*line;

	// error cases
	if (BUFFER_SIZE < 1 || fd <= 0)
		return (NULL);
	// allocate some memory into buffer
	if (!buffer)
		buffer = (char *)malloc(sizeof(char) * 1);
	// read the file into buffer
	buffer = read_file(fd, buffer);
	//now the buffer has the whole chunk of strings from fd,
	//extract each line out one by one.
	line = extract_line(buffer);
	buffer = ft_nextchunk(buffer, ft_strlen(line));
	return (line);
}
/**
int main(void) {
    int fd;
    char *result;
    char *buffer;

    // Open the example.txt file for reading
    fd = open("example.txt", O_RDONLY);

    // Check if the file was opened successfully
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Allocate memory for the buffer
    buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buffer) {
        perror("Memory allocation error");
        close(fd);
        return 1;
    }

    // Initialize the buffer
    buffer[0] = '\0';

    // Read from the file using read_file
    result = read_file(fd, buffer);

    // Check the result and print the final text
    if (result != NULL) {
        printf("Final text printed:\n%s\n", result);
        free(result);  // Free the result
    } else {
        printf("read_file returned NULL\n");
    }

    // Close the file and free the buffer
    close(fd);
    free(buffer);

    return 0;
}

**/
/**
void test_ft_nextchunk(char *buffer, size_t len) {
    printf("Original buffer: %s\n", buffer);

    char *result = ft_nextchunk(buffer, len);

    if (result == NULL) {
        printf("Test failed: NULL result\n");
    } else {
        printf("Extracted chunk: %s\n", result);
        ft_free(result);
    }
}

int main(void) {
    printf("Test 1 - Normal case:\n");
    char *buffer1 = "This is a test.";
    test_ft_nextchunk(buffer1, 5);

    printf("\nTest 2 - Buffer is NULL:\n");
    test_ft_nextchunk(NULL, 5);

    printf("\nTest 3 - Invalid length (greater than or equal to buffer length):\n");
    char buffer3[] = "Another test.";
    test_ft_nextchunk(buffer3, 15);
    test_ft_nextchunk(buffer3, ft_strlen(buffer3));

    printf("\nTest 4 - Empty buffer:\n");
    char buffer4[] = "";
    test_ft_nextchunk(buffer4, 0);

    return 0;
}
**/
/**
void test_extract_line(char *buffer) {
    char *line = extract_line(buffer);

    if (line == NULL) {
        printf("Test failed: NULL line\n");
    } else {
        printf("Extracted line: %s\n", line);
        free(line);
    }
}

int main(void) {
    printf("Test 1 - Non-empty buffer:\n");
    char buffer1[] = "This is line 1.\nThis is line 2.\nThis is line 3.\n";
    test_extract_line(buffer1);

    printf("\nTest 2 - Empty buffer:\n");
    char buffer2[] = "";
    test_extract_line(buffer2);

    printf("\nTest 3 - Line without newline:\n");
    char buffer3[] = "This is a line without a newline.";
    test_extract_line(buffer3);

    return 0;
}
**/
int	main(void)
{
	char	*line = NULL;
	int	fd;
	int	i;

	fd = open("example.txt", O_RDONLY);
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			return (0);
		printf("LINE %d: %s",i++, line);	
	}
}
