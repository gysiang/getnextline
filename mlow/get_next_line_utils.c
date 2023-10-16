/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:13:12 by mlow              #+#    #+#             */
/*   Updated: 2023/10/16 15:38:49 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char **f)
{
	if (*f)
	{
		free(*f);
		*f = NULL;
	}
	return (NULL);
}
//
/*
------------------------------------------------------------------------------
Firstly, the reason why the ft_free can be used by itself, is because 
functions that return a pointer (char *) can be called and used without
needing to assign their return value to a variable.

for "char *ft_free(char **f)", the return value is not used or assigned to any 
variable because primary purpose is to modify value of "f".


Also just in case you missed it, here is the notes from the get_next_line.c:
------------------------------------------------------------------------------
char	*ft_free(char **f)
{
	if (*f)
	{
		free(*f);
		*f = NULL;
	}
	return (NULL);
}
char **f means it is the memory address of a pointer to a string.
What this means is that when you pass a pointer to a pointer as an 
argument to this function, you can modify the original pointer.

We usually do this when you want to free allocated memory and 
ensure that the original pointer pointing to the memory is properly updated 
to NULL to avoid potential dangling pointers.

For example, if "*f" value is "lorem", once we free(*f), we may have
made the string inaccessable but they still contain the memory address.
In other words, they can still be called out, thus memory leak.
Thats why we also NULL the "*f" tp make it invalid cause the memory location
now no longer exist.
To look at it the other way, when you free, you killed everyone inside 
the house. But their corpses are still there. So you NULL to clean the house.

Perfect, now you can resell the house, claiming it free from haunted spirits.
You don't just kill the address of the house you went to their actual house.

Summary, *f means you modify only that copy of the value in the ft_free.
Not the original self in other functions it may exist.
While **f means that any changes reflected in that ft_free working will
be reflected back to the original in other functions. We are directly
modifying the value.
------------------------------------------------------------------------------
*/
//

char	*str_combined(char *buf, char *stored_data)
{
	char	*temp_data;

	temp_data = stored_data;
	stored_data = ft_strjoin(temp_data, buf);
	ft_free(&temp_data);
	return (stored_data);
}
//
/*
------------------------------------------------------------------------------
Lastly, str_combined joins two strings together with the help of strjoin.

-char    *temp_data;
Is used as temporary stored_data to be freed later.


"
        temp_data = stored_data;
        stored_data = ft_strjoin(temp_data, buf);
        ft_free(&temp_data);
        return (stored_data);
"
We need to create a temp_data in the first place is because 
"stored_data = ft_strjoin(stored_data, buf)" is wrong.
Why? Because it is: 
1)to avoid memory loss/leaks.
if you reassign stored_data without copying its value over
to another pointer, you will lose the reference to the memory
previously allocated, losing the chance to free "THAT" stored_data.
------------------------------------------------------------------------------
*/
//

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	str1;
	size_t	str2;
	char	*newstr;

	str1 = 0;
	str2 = 0;
	newstr = (char *)malloc(sizeof(char)
			* ((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (!newstr)
		return (NULL);
	while (s1[str1] != '\0')
	{
		newstr[str1] = s1[str1];
		str1++;
	}
	while (s2[str2] != '\0')
	{
		newstr[str1 + str2] = s2[str2];
		str2++;
	}
	newstr[str1 + str2] = '\0';
	return (newstr);
}

size_t	ft_strlen(const char *s)
{
	size_t	length_so_far;

	length_so_far = 0;
	while (s[length_so_far] != '\0')
	{
		length_so_far++;
	}
	return (length_so_far);
}

char	*ft_strchr(const char *s, int c)
{
	int		num_source;
	char	character;

	character = (char)c;
	if (character == '\0')
		return ((char *)s + ft_strlen(s));
	num_source = 0;
	while (s[num_source] != '\0')
	{
		if (s[num_source] == character)
			return ((char *)s + num_source);
		num_source++;
	}
	return (NULL);
}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//Notes from my working days just in case:
//An idea of learning suggested
// by Aaron is to write out the program
// using english to figure how to solve
// the question without relying on
// others, you should only ask when
// you know where is wrong.
//
//Objective of the get_next_line:
// write a function that returns
// a line read from a file descriptor
//
// Return value:
// Read line: correct behavior
// NULL: nothing to read/ error occured.
//
// we can use: read, malloc, free.
//
//https://en.wikipedia.org/wiki/File_descriptor
// What is file descriptor?
//It is a non-negative int file where if it
// was negative it would refer to no values
// or error conditions.
//
// fd are part of 3 standard <stdio.h> streams:
// int 0, int 1, int 2. 
// 0 - standard input(stdin)
// 1 - standard output(stdout)
// 2 - standard error (stderr)
//
//these 3 standard streams for fd are opened
// by all process called the file table.
//
//This file table uses stuff like open(),
// read() & write() functions.
//"******"
//The file table is connected into another table
// called the "indoe table" that describes actual
// files. "Q)"Does this mean file location?
// eg: /home/joe/wikidb or /home/marcus/get_new_line.
//"****"
// To perform input or output, the process goes through
// fd via a system call. "Q)" what is system call?
// are they like examples open()?
//https://www.tutorialspoint.com/system-calls-in-unix-and-windows
//
//Back to fd, we access the path like ./text.txt.
//
//The first thing we should do is understand
// the project requirements. 
//:Our objective is
// to basically read 'a' single line from
// the file and return it as a string.
//It should be capable to handle mutliple
// 1) multiple file desciptors,
// 2) end of file.
// 3) errors.
// 4) Large files that may not fit into
// memory.
//
//We must compile with the flag
// -D BUFFER_SIZE=xx
//
// This will make us learn about open(),
// close() & read() functions along with
// static variables and file descriptors.
//
// "common approach is to read file line by line
// "into a buffer and then extract the lines"
// "from the buffer."
//
// Use a loop to read a file in chunks and append
// each of them into a buffer(buf). Then scan
// the buffer for newlines and extract the lines
// as you find them.
//
// Examples of edge cases, 
// 1) File ends and no newline characters at end 
// of buffer.
//
// use helper functions such as extracting a single
// line from buffer and return it as a string.
//
//Open() function:
//https://linuxhint.com/c-language-o_donly-o_wrongly-and-o_rdwr-flags/
// A system call that create/open file mentioned in
// pathname.
// e.g: open("./file.txt", O_RDONLY);
//
// The return value of open is the new file descriptor
// (a non-negative integer) or -1 if an error occured(errno).
// Open function uses the following flags:
// 1)O_RDONLY (read only)
// 2)O_WRONLY (write only)
// 3)O_RDWR (read/write)
//
// There are more flags, refer to them when u need it.
//
//Close() function:
//
//
// write plan first: use the above as reference.
//
//Understand what does open() & close() do.
/*
  Basically, "open()" function creates the opportunity to use
   the read() function. Because with open(), inside you can see
   the word O_RDONLY which means read only. This means thanks
   to this, we can use the read function to obtain the "byte_read"
   as well as the characters that it reads in "fd" and stores 
   inside "buf". What bytes and characters it can read is limited
   by the "BUFFER_SIZE".
   
  -e.g: byte_read = read(fd, buf, BUFFER_SIZE);
   
  Anyways back to topic, the next part is the while loop,
   which we use to get the value of the get_next_line.
   We call out the get_next_line(fd) and everytime it gets
   called out, it will continue until the entire file is read.

   "Q)" Why do we do we free(buf)?
    Not really impt since its just a test case, but we need to
    free it cause we use malloc inside of get_next_line which
    buf got the value from.

   Once you finished using the fd, close(fd) it. This will cause
   the fd to be no longer usable, ending the program with 
   return (0).
 */
//
//
/* Notes:
  *(The idea of the function get_next_line, is to read the text file
   pointed to by the fd(file descriptor) one line at a time.

  It is possible for one line to contain more than 100 words like 
   an essay. Thus there might be situations where if you wrote
   a BUFFER_SIZE 10, it might not be enough and thus the reason
   we use "static variable stored_data" to keep the characters we
   read.)*

   We first start off the objective of using the read function.
   BUT BEFORE THAT,
   lets list off what we need to do in "get_next_line(int fd)"
   	1) use read function to get bytes_read & buf.
	2) With both values obtained, now store the data
       	& print out the value until and including newline '\n'
	3) Handle the case if fd = 0 or fd < 0.
	4) Handle the case when fd hits '\n' or NULL.
	5) Handle the case of different values of BUFFER_SIZE	

 */
// Thought process:
// To start get_next_line, include the following variables.
// 1) static variable "stored_data"
// 2) ssize_t variable that contains bytes_read "bytes_read"
// 3) char variable that will contain the characters obtained
// from using the read() function "buf"
// 4) add "BUFFER_SIZE" to get_next_line.h 
// 
// Start process thoughts addons:
// 1) To even use both "buf" & "stored_data" we need to malloc 
// them.
// 2) Before mallocing them, we need to handle the case if 
// fd is less than 0 (fd < 0). Normally fd is unsigned int, but
// due to this question, we need to handle that case ourselves.
// 3) every time you create a malloc for a variable, ensure you
// have the condition should their malloc = 0, return NULL.
// 4) bytes_read = read(fd, buf, BUFFER_SIZE);
// at this point, we need to start reading the output.
// My thoughts at this moment are: do we need to make a
// helper function to handle this output? we need to read
// the line one each time so do we use a while loop? or nay?
// I decided to go with a helper function to get the output of
// the line.
// 5) Creating malloc for stored_data, ran into the issue on 
// how to malloc since it isnt BUFFER_SIZE + 1.
// 	How it was: 
// stored_data = (char *)malloc(("ft_strlen()" + 1) * (sizeof(char))
//
// 6) Now the idea is that we need to obtain the size so that
// we can read both the current values we plan to store and
// the next values of line we will store. We need to add in
// a variable that increases the count on it's own.
// 7) I could create a variable called index to read the file
// one at the time but this mean we should do this inside
// a helper function. "int stored_size".
//
//-day2-
// 9)Okay after calming down turns out that you can solve 
// this issue by giving the stored_data a malloc value of 1.
// Then after giving the value of '\0', the stored_data becomes
// an empty string. 
// Once it is an empty string, u can obtain the new value of 
// malloc from using "strjoin"(I will recreate it myself, after
// all, we cannot use libft functions but we can recreate it
// to become something similar). Now we send it over to 
// "line_ext to extract the line".
// 10) After checking online resources, i noticed that my
// current get next line needs improvement to handle case
// if buf allocation fails when the get_next_line gets 
// called again especially since my int main() is a while
// loop.
//
// In other words, "should my buf allocation fails", i will 
// also need to free my "stored_data" & "buf".
//
// Thus my if(buf) need to be updated. Here is the old code:
/*
char    *get_next_line(int fd)
{
        static char     *stored_data;
        char            *buf;
        ssize_t         bytes_read;
        char            *line;

        if (fd < 0 || BUFFER_SIZE < 1)
                return (NULL);
        buf = (char *)malloc((BUFFER_SIZE + 1) * (sizeof(char)));
        if (!buf)
                return (ft_free(buf));
*/
//Here is the updated:
/*
char    *get_next_line(int fd)
{
        static char     *stored_data;
        char            *buf;
        ssize_t         bytes_read;
        char            *line;

        if (fd < 0 || BUFFER_SIZE < 1)
                return (NULL);
        buf = (char *)malloc((BUFFER_SIZE + 1) * (sizeof(char)));
        if (!buf)
	{
		free(stored_data);<-------------------------
                return (ft_free(buf));
	}
*/
//
//Now with that out of the way.... lets go to line_ext->
//11) The objective of line_ext is to extract the lines 
// obtained inside the buf. Then after storing, we print 
// out the line until '\n'(newline) or repeat process if
// we havent read '\n' or until NULL (if there is no more
// '\n' or if it doesn't exist in the first place).
// Also once you return the line that reads until which
// also includes the '\n', the ones after '\n' will be
// stored to be read again for future uses.
//
//12) decided to create a helper function that does
// what i wrote in my old working, using void, obtain
// the value of buf and bytes read and handles the case
// when get_next_line is called again and stores the 
// static values of the old lines read that went past
// the previous '\n'.
/*
char	*get_next_line(int fd)
{
	static char	*stored_data;
	char		*buf;
	ssize_t		bytes_read;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
here--->buf = (char *)malloc((BUFFER_SIZE + 1) * (sizeof(char)));
	if (!buf)
	{
		free(buf);
		return (ft_free(stored_data));
	}
till--->bytes_read = read(fd, buf, BUFFER_SIZE);
	if (!stored_data)
	{
		stored_data = (char *)malloc((1) * sizeof(char));
		if (!stored_data)
			return(ft_free(stored_data));
		*stored_data = '\0';
	}
	line_ext(fd, buf, bytes_read, stored_data);
}
*/
// 
//
// Start process:
// 1) The edge case at the start of get_next_line isnt enough,
// we need to case for "BUFFER_SIZE < 1" & "(frank) fd > OPEN MAX".
// 2) Give the stored_data malloc value so that it can start
// storing data 
// 3) we need a variable to sumbit the lines we obtained and
// return. "char *line"
//
//
