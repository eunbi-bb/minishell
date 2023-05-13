/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 16:10:21 by eucho         #+#    #+#                 */
/*   Updated: 2022/12/21 14:03:29 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* 
	DESCRIPTION
		strdup() is used to duplicate a string.
	RETURN VALUE
		Returns a pointer to null-terminated byte string.
		- "null-terminated byte string" is a sequence of nonsero bytes
		followed by a byte with value zero.   
*/
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	size;
	char	*str;

	size = ft_strlen(s1) + 1;
	str = (char *)malloc(size);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, size);
	return (str);
}
