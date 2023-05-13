/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 16:08:42 by eucho         #+#    #+#                 */
/*   Updated: 2022/10/24 15:27:43 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
	DESCRIPTION
		memchr() searched for the first occurrence of the character 'c'
		in the first 'n'bytes of the string pointed to, by the argument '*s'.
	
	RETURN VALUE
		Returns pointer or NULL if the character does not occure 
		in the given memory area.
*/
#include <stdlib.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s2;

	i = 0;
	s2 = (unsigned char *)s;
	while (i < n)
	{
		if (s2[i] == (unsigned char)c)
			return (&((unsigned char *)s2)[i]);
		i++;
	}
	return (NULL);
}
