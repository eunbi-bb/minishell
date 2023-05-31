/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 16:10:04 by eucho         #+#    #+#                 */
/*   Updated: 2023/01/14 20:16:28 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* 
	DESCRIPTION
		Allocates and returns an array of strings obtained by splitting 's'
		using the character 'c' as a delimiter. The array must end with a NULL pointer.
	RETURN VALUE
		Returns the array of new strings resulting from the split.
		NULL if the allocation fails.
*/
#include "libft.h"

size_t	word_counter(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			count++;
			while (*s != '\0' && *s != c)
				s++;
		}
		else
			s++;
	}
	return (count);
}

void	*free_pointer_array(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	unsigned int	i;
	const char		*start;
	char			**str;

	if (!s)
		return (NULL);
	str = (char **)malloc(sizeof(*str) * (word_counter(s, c) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		start = s;
		while (*s && *s != c)
			s++;
		if (*(s - 1) != c)
			str[i++] = ft_substr(start, 0, s - start);
		if (i)
			if (str[i - 1] == NULL)
				return (free_pointer_array(str - (i - 1)));
	}
	str[i] = 0;
	return (str);
}
