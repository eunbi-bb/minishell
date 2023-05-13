/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 16:10:10 by eucho         #+#    #+#                 */
/*   Updated: 2022/12/21 14:03:24 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* 
	DESCRIPTION
		strchr() searches for the first occurrence 'c' in 's'. 
	RETURN VALUE
		Returns NULL if the character is not found.
		Returns a pointer to the first occurrence of the character 'c' in 's'. 
*/
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s);
	while (i <= len)
	{
		if (s[i] == (char)c)
			return (&((char *)s)[i]);
		i++;
	}
	return (NULL);
}
