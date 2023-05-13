/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 16:08:57 by eucho         #+#    #+#                 */
/*   Updated: 2022/10/24 15:27:56 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
	DESCRIPTION
		memcpy() copies 'n' characters from '*src' in to '*dst'.
		const means readonly.
	
	RETURN VALUE
		A pointer to the destination.
*/
#include <stdlib.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dst && !src)
		return (NULL);
	if (dst == src)
		return (dst);
	while (i < n)
	{
		((char *)dst)[i] = ((char *)src)[i];
		i++;
	}
	return (dst);
}
