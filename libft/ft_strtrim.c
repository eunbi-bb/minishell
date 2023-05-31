/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 16:12:24 by eucho         #+#    #+#                 */
/*   Updated: 2022/12/21 14:04:06 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
	DESCRIPTION
		strtrim() allocates and returns a copy of '*s1' with tha characters
		specified in '*set' removed from the beginning and the end of the string.
	RETURN VALUE
		returns the trimmed string.
		NULL ig the allocation failed.
*/
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		front;
	int		back;
	char	*str;

	str = 0;
	if (!set)
		return (ft_strdup(s1));
	front = 0;
	back = ft_strlen(s1);
	while (s1[front] && ft_strchr(set, s1[front]))
		front++;
	while (back > front && ft_strchr(set, s1[back - 1]))
		back--;
	str = (char *)malloc(sizeof(char) * (back - front + 1));
	if (!str)
		return (NULL);
	if (str)
		ft_strlcpy(str, &s1[front], back - front + 1);
	return (str);
}
