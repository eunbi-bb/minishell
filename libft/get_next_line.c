/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/05 09:14:52 by eucho         #+#    #+#                 */
/*   Updated: 2023/02/15 21:50:37 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
	read()
    	returns bytes if it reads a line.
    	return 0 if it reached the end of file
    	return -1 if it has an error. -> NULL

	read_line()
		Takes "fd" and saves what read from it on "str".
		And join it to "content" for the persistence.
		Iterates until strchr() finds '\n'.
		"content" = the pointer to static var from previouse run.
		byte value will be the length of string. So add '\0'
		to complete one line. Then put the "str" to "content".
		In strjoin() won't be needed the "str" after copying.
		So free "s1"(= str) is needed.
		returns the new static var.

	copy_line()
		copies a line (that is divided by '\n').
		First calculate the length of string as incrementing 'i'
		until it meets '\n'. And malloc it with extra 2 size
		for '\n' and '\0'.
		returns "one" line.
	
	next_content()
		Save the "content" that the one line is removed.
		If the previously copied line finishes with '\0',
		then returns NULL.

	MAXIMUM NUMBER FD that library supports
		MacOS DEFAULT = 10240
*/

#include "libft.h"

char	*next_content(char *content)
{
	char	*str;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = gnl_strlen(content);
	while (content[i] && content[i] != '\n')
		i++;
	if (!content[i])
		return (free(content), NULL);
	str = malloc(sizeof(char) * (len - i + 1));
	if (!str)
		return (NULL);
	i++;
	while (content[i])
		str[j++] = content[i++];
	str[j] = '\0';
	free(content);
	return (str);
}

char	*copy_line(char *content)
{
	int		i;
	char	*str;

	i = 0;
	if (!content[i])
		return (NULL);
	while (content[i] && content[i] != '\n')
		i++;
	str = malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	gnl_strlcpy(str, content, i + 2);
	return (str);
}

char	*read_line(int fd, char *content)
{
	char			*str;
	int				byte;

	str = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!str)
		return (NULL);
	byte = 1;
	while (byte != 0 && gnl_strchr(content, '\n') == NULL)
	{
		byte = read(fd, str, BUFFER_SIZE);
		if (byte == -1)
		{
			free (str);
			return (free(content), NULL);
		}
		str[byte] = '\0';
		content = gnl_strjoin(content, str);
	}
	free (str);
	return (content);
}

char	*get_next_line(int fd)
{
	char			*line;
	static char		*content[10240];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	content[fd] = read_line(fd, content[fd]);
	if (!content[fd])
		return (NULL);
	line = copy_line(content[fd]);
	content[fd] = next_content(content[fd]);
	return (line);
}
