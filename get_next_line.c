/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 12:53:43 by gyong-si          #+#    #+#             */
/*   Updated: 2023/10/07 14:31:14 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*get_next_line(int fd)
{
	char	*line;
	return (*line);
}

// 1. open the file and save it into a buffer
// 2. if nothing to read or error, return null
// 3. do a while loop
//       call get_next_line, to check for \n, print including \n
// 4. if end of file does not have \n, print excluding \n 
