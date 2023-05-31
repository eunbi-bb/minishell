/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 16:12:13 by eucho         #+#    #+#                 */
/*   Updated: 2022/12/21 14:03:50 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
	DESCRIPTION
		strnstr() function locates the	first occurrence of '*little' in '*big', 
		where not more than	len characters are searched.
		Characters that appear after a `\0' character are not searched.
	RETURN VALUE
		If '*little' is an empty string, '*big' is returned.
		If '*little' occurs nowhere in	'*big', NULL is returned.
		Otherwise a pointer to the first character of the first occurrence of 
		'*little' is returned.
*/
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	little_len;

	i = 0;
	if (*little == '\0')
		return ((char *)big);
	if (!*big)
		return (NULL);
	little_len = ft_strlen(little);
	while (i < len && *big)
	{
		if (ft_strncmp(big, little, little_len) == 0)
		{
			if (len < little_len + i)
				return (NULL);
			return ((char *)big);
		}
		big++;
		i++;
	}
	return (NULL);
}
