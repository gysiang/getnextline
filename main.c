/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 13:40:45 by gyong-si          #+#    #+#             */
/*   Updated: 2023/10/07 13:41:01 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main() {
    int fd;  // File descriptor
    char buffer[BUFFER_SIZE];  // Buffer to read into

    // Open the file for reading
    fd = open("example.txt", O_RDONLY);
    if (fd == -1) {
        perror("Unable to open the file");
        exit(EXIT_FAILURE);
    }

    // Read from the file into the buffer
    ssize_t bytesRead = read(fd, buffer, BUFFER_SIZE);
    if (bytesRead == -1) {
        perror("Unable to read the file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Print the read data
    printf("Read %zd bytes: %.*s\n", bytesRead, (int)bytesRead, buffer);

    // Close the file
    close(fd);

    return 0;
}

