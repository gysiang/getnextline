/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:54:49 by mlow              #+#    #+#             */
/*   Updated: 2023/10/16 15:39:33 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_static_line(char *str)
{
	unsigned int	num_s;
	unsigned int	num_st;
	char			*new_str;

	num_s = 0;
	while (str[num_s] && str[num_s] != '\n')
		num_s++;
	if (!str[num_s])
		return (ft_free(&str));
	new_str = (char *)malloc((ft_strlen(str) - num_s + 1) * (sizeof(char)));
	if (!new_str)
		return (NULL);
	if (str[num_s] == '\n')
		num_s++;
	num_st = 0;
	while (str[num_s + num_st])
	{
		new_str[num_st] = str[num_s + num_st];
		num_st++;
	}
	new_str[num_st] = '\0';
	ft_free(&str);
	return (new_str);
}

static char	*line_ext(char *stored_data)
{
	int		index;
	char	*line_read;

	index = 0;
	while (stored_data[index] && stored_data[index] != '\n')
		index++;
	line_read = (char *)malloc((index + 2) * (sizeof(char)));
	if (!line_read)
		return (NULL);
	index = 0;
	while (stored_data[index] && stored_data[index] != '\n')
	{
		line_read[index] = stored_data[index];
		index++;
	}
	if (stored_data[index] == '\n')
	{
		line_read[index] = '\n';
		index++;
	}
	line_read[index] = '\0';
	return (line_read);
}

static char	*bufstored_data(int fd, char *stored_data)
{
	char		*buf;
	ssize_t		bytes_read;

	buf = (char *)malloc((BUFFER_SIZE + 1) * (sizeof(char)));
	if (!buf)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(stored_data, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			ft_free(&stored_data);
			return (ft_free(&buf));
		}
		buf[bytes_read] = '\0';
		stored_data = str_combined(buf, stored_data);
	}
	ft_free(&buf);
	return (stored_data);
}

char	*get_next_line(int fd)
{
	static char	*stored_data;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!stored_data)
	{
		stored_data = (char *)malloc((1) * sizeof(char));
		if (!stored_data)
			return (NULL);
		*stored_data = '\0';
	}
	stored_data = bufstored_data(fd, stored_data);
	if (!stored_data)
		return (ft_free(&stored_data));
	line = line_ext(stored_data);
	if (!line || !line[0])
	{
		ft_free(&stored_data);
		return (ft_free(&line));
	}
	stored_data = ft_static_line(stored_data);
	return (line);
}
/*
int	main(void)
{
	int		fd;
	char	*buf = NULL;
	
	fd = open("./epic.txt", O_RDONLY);
	while ((buf = get_next_line(fd)) != NULL)
	{
		printf("Static line: %s\n", buf);
		free(buf);
	}
	printf("\nStatic line: %s\n", buf);
	printf("\nStatic line: %s\n", buf);
//	while ((get_next_line(fd)) != NULL)
//	{
//		printf("\nStatic line: %s\n", get_next_line(fd));
//		free(get_next_line(fd));
//	}
	close(fd);
	return (0);
}
*/
/*
Objective of get_next_line:
To read the line(s) provided by "fd" file descriptor.
What it means is that whenever "printf" is called, we
are to print out the first line of values until the '\n'(newline).
Then we start from the beginning after THAT '\n'(newline), 
and then read until the 2nd '\n'(newline).
Each of the lines we are reading are to be separated by the 
'\n'(newline) until we hit EOF(End of file) which is NULL('\0').
- We are to use "read", "malloc" & "free" for this program.

To get started, we need to learn what is read:
The read function returns the number of bytes_read. 
What it means is that read() function gets the count bytes from fd 
which then goes into the buffer(buf). 
-Should the bytes_read count is 0, errors may be detected(-1) or 0 is returned. 
-0 indicates EOF while -1 is error (for bytes_read)
-ssize_t read(int fd, void *buf, size_t count);

Now we know what the read function does, we need to learn and start our program 
with the file "open()" & end with "close()" functions.
So what are they?
Firstly, they require the libraries:#include <fcntl.h>
& probably <stdio.h>... ((check this too))

open() function
"int open(const char *pathname, int flags)"
-it is a system call that opens the files specified by the pathname 
written.e.g.: open("./file.txt", O_RDONLY). 
The return value of the open() function is a file descriptor(fd) 
which is usually a non-negative intthat is used in subsequent 
system calls such as read() &write(),etc functions.
There are a total of 3 relevant flags used for open() we use.They are:
1) O_RDONLY, (read only)
2) O_WRONLY (write only)3) O_RDWR (read & write)

For our project, we are not allowed to use the write function, 
thus 2) & 3) is out of the picture. thus, we use O_RDONLY.
close() function"int close(int fd)"-closes a file descriptor(fd) 
and once it happens it canno longer be used.The return values:
1)0 on success2) -1 on error
For int main(void)1) We first open the fd @ int main, 
this will allow us to use the function read in our get_next_line.
2) we then 'send over' the fd to get_next_line(int fd). 
What we send over is depending on what we typed in the open() function 
@ the int main(void) and how many lines we read including the newline is 
based on how many times we call the get_next_line.
3) Once you write them, close the function to end the fd usage, return (0).
4) Now with the value "fd", you can now use a read function inside the
get_next_line function to get the total no. of bytes that you can get each line.
5) With both the byte_read and characters inside buf obtained, you will need to
use static variable to keep track of the characters you can read at one time
UNTIL you hit the '\n'(newline).
*keep track of null
6) with your line obtained, you stored them. However, depending on your
BUFFER_SIZE, you may read past the '\n'. The idea is that the ones before newline
 & new line itself are the line we want to print, while the ones after the 
'\n'(newline) are stored_data, waiting to be used when get_next_line is 
called again.
So we will return "line" value, while the temp data are continued to be stored.
So that they will be combined together with str_combined with the strjoin the 
next time it is called.
However, what happens if there is no newline? We read till the null byte. That
means we read the entire thing at one shot.

BUFFER_SIZE '1',
Chances to skip past '\n' or NULL is almost impossible. Write it to read 
'\n' or NULL byte.

BUFFER_SIZE ">1",
May have the chance to read past '\n' or NULL byte. You will need to handle
both the newline & NULL byte. And you will also need to handle the case
where you may go past the '\n'(newline), which you will have to return 
"those before the '\n'(newline)" while storing temp_data past newline.
------------------------------------------------------------------------------

Just checking but do you still remember at this point how do you know
when you reached the EOF(End of file)?. What is the value at the end
of the file? How do you know or how will you make the system know
the file ends?
- "The program ends when it hits the null byte '\0', that is the EOF".
- '\n' only ends that function call get_next_line for THAT printf.

Btw, should the system contiune to read but then you tried to edit the file
while it is reading, you will cause UNDEFINED BEHAVIOUR.

Speaking of which, do you know what does each fd(file descriptor) means?
fd(0) = standard input (stdin)
fd(1) = standard output (stdout)
fd(2) = standard error (stderr) - also contains all error messages

------------------------------------------------------------------------------
*/
//
/*
Now to start with get_next_line. We start with the most basic question.
"What is static variable?"
It is a variable that retains it's value across multiple call functions.
Compare to normal variables, they only exist during that call function,
repeatingly giving the same values over and over again should you keep
calling them. e.g printf.

HOWEVER, static function will only return to it's original value ONCE
the "PROGRAM" ends. That means the end of the int main(void).
They remmeber the first set of values and remembers them throughout the
function call.
1)"They have longer storage duration and are reserved in a fixed location
in memory".
2)"They exist from point of declaration to the end of program's execution"
3)"should static variable not be explicity initialized, it starts off as 
0/NULL if pointer." when program starts - Initialization.
4)"Limited to the function which it is declared it is literally static",
only accessible to that perticular function, a local "variable".
5)"They retain their values in between function calls, useful for stuffs
such as counters or maintaining state information across multiple calls".
-Preservation of value.
*/
//
/*
------------------------------------------------------------------------------
char	*get_next_line(int fd)
{
	static char	*stored_data;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);

->"starts by checking if(fd && BUFFER_SIZE) used are valid."
fds cannot be less than 0 as they are supposed to act like unsigned int.
while there are no such thing as BUFFER_SIZE < 1.

Should either condition become true, we handle that by returning NULL to 
end the function to indicate an error.
------------------------------------------------------------------------------

	if (!stored_data)
	{
		stored_data = (char *)malloc((1) * sizeof(char));
		if (!stored_data)
			return (NULL);
		*stored_data = '\0'; <- empty string.
	}
-> "The idea behind this working is so that i can use the function strjoin"
You do not want to malloc stored_data again once the get_net_line gets called.
Thus this condition protects/ensures that it will only happen "once".

Beware: I know you might be wondering about EOF(End of file) where should you
finish reading the entire file, your static variable will be left with 
value '\0'. Do take note, "!store_data" & "!stored_data[0]" are not the same.
(!stored_data) Checks if it's a NULL pointer while (!stored_data[0]) checks 
for NULL byte '\0'. 
About NULL pointer, its condition is when it points to '\0' in memory, in
other words, it does not point to any object or function, becoming invaild.
Which we don't use.
THUS, this just reconfirms that for our project, the '\0' NULL byte is
to indicate the end of the file.

Now back to this part:
"stored_data = (char *)malloc((1) * sizeof(char))"
The reason why i give the static variable a value of malloc(1) is because 
i wish to empty the string so that i can use it inside my strjoin function.

Now you might ask, why not malloc(0) or why do we need to do:
"*stored_data = '\0'".
Answer:
1) stored_data = '\0' is essential because it initializes the first byte of 
allocated memory with NULL character, which marks the end of string in C.
Without this initialization, the memory return could contain arbitrary data
 or undefined behaviour.
In other words, every "string" must be null terminated just like how we 
always do.
2)There is no such athing as malloc(0). While u can do so, it just cause 
memory errors. Just don't do it.
3)An empty string which is malloc allocated can be combined to another
empty string. Without doing malloc allocation, the result would be we will
be writing to an unknown memory location which will lead to errors cause
of undesired behaviours such as segmentation fault or memory corruption
due to overlapping with other parts of the program.
------------------------------------------------------------------------------

	stored_data = bufstored_data(fd, stored_data);
*<refer to bufstored_data>

-> "bufstored_data function is called to give the stored_data the total
characters read as allowed by BUFFER_SIZE from fd(file descriptors)."
This step is responsible for reading and storing_data.
------------------------------------------------------------------------------

	if (!stored_data)
		return (ft_free(&stored_data));

-> "After obtaining the updated stored_data", we need to check if it is still
NULL. the ft_free frees memory & sets that pointer to NULL.
------------------------------------------------------------------------------

	line = line_ext(stored_data);

-> "Calls the line_ext function which objective is to extract a line from 
stored_data". The idea is that if BUFFER_SIZE go past the '\n'(newline), 
the line will extract from stored_data and obtain the lines up till & 
including the character '\n'(newline).

	if (!line || !line[0])

-> "Checks if line is either a NULL pointer or contains a NULL byte"
Should above condition be true:

	{
		ft_free(&stored_data);
		return (ft_free(&line));
	}

->"Free both line & stored)data and return NULL"
we freed the stored_data as well cause it is used to store data read
from the file. After it is processed, we need to free it to prevent 
memory leaks and NULL it after to invalid it.
-We also need to free & clean line "return (ft_free(&line))" as well
since it's the last part(EOF) and we don't need them both anymore.

	stored_data = ft_static_line(stored_data);

->"Now, the reason why we do this again is simple, should the 
function gets called again, it will print /obtain the next set of lines
until the next '\n'(newline)".
-We "DO NOT" free this function or do an if() case cause we still need
it for the next call function. It is designed- with the assumption 
that it is a valid allocated buffer(In other words, not a NULL pointer).
The other functions before it should have resolved & handled those
issues before ft_static_line happens.

	return (line);
}
*/
//
//
/*
Now we go through the first function in the list we used:
"static char	*bufstored_data(int fd, char *stored_data)"
-What this function does is it takes fd(file descriptor) & a pointer 
to a character buffer "stored_data".

------------------------------------------------------------------------------

static char	*bufstored_data(int fd, char *stored_data)
{
	char		*buf;
	ssize_t		bytes_read;

-> "char *buf" is used to read the fd file's characters, it's contents.
While "ssize_t bytes_read" tracks the no. of bytes read from read() function.
------------------------------------------------------------------------------

	buf = (char *)malloc((BUFFER_SIZE + 1) * (sizeof(char)));
	if (!buf)
		return (NULL);

-> "we malloc buf so that it can accommodate the character we read
from file to temporary hold data read from file."

	bytes_read = 1; "<- to enter the loop below"

------------------------------------------------------------------------------
	while (!ft_strchr(stored_data, '\n') && bytes_read != 0)

-> "The idea is that we read the current set of stored_data and repeat 
until we already read it has '\n' or bytes_read is = 0".
	
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);

------------------------------------------------------------------------------

		if (bytes_read < 0) "<- checks if bytes_read returned an error -1"
		{
			ft_free(&stored_data);"<- must be done"
			return (ft_free(&buf));
		}

-> "This part is very important".
The reason why we ft_free the stored_data here before we return it, is to 
ensure that we do not call it again since there is nothing to read.
If you do not do this, the follow errors occur:
1)
1 bytes in 1 blocks are definitely lost in loss record 1 of 2
at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
by 0x110663: get_next_line (get_next_line.c:101)
by 0x10AE6C: gnl(int, char const*) (gnl.cpp:20)
by 0x10D157: main (mandatory.cpp:29)
2)
1 bytes in 1 blocks are definitely lost in loss record 2 of 2
at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
by 0x110663: get_next_line (get_next_line.c:101)
by 0x10AE6C: gnl(int, char const*) (gnl.cpp:20)
by 0x10D185: main (mandatory.cpp:29)

------------------------------------------------------------------------------
		buf[bytes_read] = '\0'; "<- simple, Null terminate"
		stored_data = str_combined(buf, stored_data); "<- combine both"
	}
	ft_free(&buf); "<- free once we no longer have any use for it".
	return (stored_data);
}
*/
//
//
//
/*
Now we go to the next part:
"static char	*line_ext(char *stored_data)"

static char	*line_ext(char *stored_data)
{
	int		index;
	char	*line_read;


->"The function (line_ext) takes a character pointer (stored_data) as input."
index is Used to track position of stored_data & char *line_read is what 
we are returning for printf in int main(void).
------------------------------------------------------------------------------
	index = 0;
	while (stored_data[index] && stored_data[index] != '\n')
		index++;

->"The purpose of the code is to figure out the total length of the size 
required to give line_read malloc allocation to read the entire stored_data."
(determine length of line to be extracted)

	line_read = (char *)malloc((index + 2) * (sizeof(char)));
	if (!line_read)
		return (NULL);

-> "We used malloc(index + 2) bcause we need to handle both '\n' & '\0'"
	
	index = 0; "<- reset counter"
	while (stored_data[index] && stored_data[index] != '\n')
	{
		line_read[index] = stored_data[index];
		index++;
	}

->"While loop is used to check if the stored_data[index] at that counter is
NOT currently a NULL terminator, or a '\n'(newline)"
-Should condition is true, we then give the "Line_read" the value of 
stored_data until it either hits a '\n'(newline), or a NULL.

	if (stored_data[index] == '\n')
	{
		line_read[index] = '\n';
		index++;
	}

->"Should the line we read and stopped has a newline, we add that in 
& increase counter by 1"

	line_read[index] = '\0';
	return (line_read);
}
Summary = line_ext extracts a line of text from stored_data string,
allocate memory to it, and return result with NULL terminated at
the end.
Should it fail, it returns NULL pointer.
*/
//
//
//
//
/*
Lastly, the final part of all of these:
"static char	*ft_static_line(char *str)"

"If you need help with imagination: refer to the most
bottom. You can use the string "pic\np" as reference
for char *str."

------------------------------------------------------------------------------

static char	*ft_static_line(char *str)
{
	unsigned int	num_s;
	unsigned int	num_st;
	char			*new_str;

->"Takes a pointer str which is bascially stored_data that was updated from
the function bufstored_data."
- Both num_s & num_st are what we use as counters(index).
-Char *new_str is what we will be giving as a return value to the function.

*remember, we are using stored_data right now as input(char *str).

------------------------------------------------------------------------------

	num_s = 0;
	while (str[num_s] && str[num_s] != '\n')
		num_s++;

->"The idea is that we want the num_s to have the value of the lenght of 
stored_data UP to '\n'."
ONCE that is done, we want to malloc the remainding characters AFTER
the '\n'(newline) in "new_str".

	if (!str[num_s])
		return (ft_free(&str));
	new_str = (char *)malloc((ft_strlen(str) - num_s + 1) * (sizeof(char)));

->"Reads the entire stored_data length & minus the ones before & including
'\n'(newline) then + 1 to include the NULL terminating byte."
So, "@ bufstored_data" function, in the line:
-"While (ft_strchr(stored_data, '\n') && bytes_read != 0)",
we will read till the '\n' anyways. 

In the condition where "BUFFER_SIZE == 1",
The ft_strlen is always 1 value higher than num_s.
So malloc (1+1) is the length of the remaining portion including 
null terminator.
------------------------------------------------------------------------------

	if (!new_str)
		return (NULL);
	if (str[num_s] == '\n')
		num_s++;

->"Should there be a '\n'(newline) character @ num_s position, we skip past
the '\n'(newline) so that we start @ the first moment where the first char
after the '\n'(newline) character is located."

	num_st = 0;
	while (str[num_s + num_st])
	{
		new_str[num_st] = str[num_s + num_st];
		num_st++;
	}

->"We will start @ the FIRST Character AFTER the '\n'(newline) character", 
which will be added inside "new_str" until all of the str is added

we will then NULL terminate the last part of "new_str[num_s]", free the 
old "stored_data = str", and return new "stored_data = new_str".

	new_str[num_st] = '\0';
	ft_free(&str);
	return (new_str);
}


*/
//
//
/*
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
You monster.
I hope you enjoy using the FREE FUNCTION NOW MUHAHAHAHAHA.
jk.

Summary, *f means you modify only that copy of the value in the ft_free.
Not the original self in other functions it may exist.
While **f means that any changes reflected in that ft_free working will
be reflected back to the original in other functions. We are directly
modifying the value.
 */
//
//
//
//
//
//
//
//
/*
Used for printf to see how the values interact.
See how you get the values based on how you use the BUFFER_SIZE value
in LIBFT.H.
static char *ft_static_line(char *str)
{
	unsigned int	num_s;
	unsigned int	num_st;
	char			*new_str;

	num_s = 0;
	while (str[num_s] && str[num_s] != '\n')
	{
		printf("\nCount after ++ %d & value %c", num_s, str[num_s]);
		num_s++;
	}
	printf("\ntotal count %d & string: %s", num_s, str);
	if (!str[num_s])
		return (ft_free(&str));
	printf("\nvalue of ft_strlen(str) %ld", ft_strlen(str));
	printf("\nvalue of num_s %d\n", num_s);
	new_str = (char *)malloc((ft_strlen(str) - num_s + 1) * (sizeof(char)));
	if (!new_str)
		return (NULL);
	if (str[num_s] == '\n')
		num_s++;
	printf("after str[num_s++]: total count %d & string: %s\n", num_s, str);
	num_st = 0;
	while (str[num_s + num_st])
	{
		new_str[num_st] = str[num_s + num_st];
		printf("%c", new_str[num_st]);
		num_st++;
	}
	printf("\nvalue of new_str: %s", new_str);
	new_str[num_st] = '\0';
	printf("\nvalue of new_str: %s\n", new_str);
	ft_free(&str);
	return (new_str);
}
*/
