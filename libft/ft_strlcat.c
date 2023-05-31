/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 16:11:18 by eucho         #+#    #+#                 */
/*   Updated: 2022/12/21 14:03:37 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* 
	DESCRIPTION
		strlcat() concatenates two strings.
		strlcat() guarantees that the total length of 
		the result string will be between the initial length of 'dst' and 'size'. 
		The zero at the end of the string is included. This function is mainly 
		used to avoid oversize of the character array.
		if size < dst, returns strlen(src) + size
		if size > dst, returns strlen(src) + strlen(dst)
	RETURN VALUE
		returns the total length of the string strlcat() tried to create.
*/
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (dst[i] && i < size)
		i++;
	while (src[j] && i + j < size - 1)
	{
		dst[i + j] = src [j];
		j++;
	}
	if (i < size)
		dst[i + j] = '\0';
	return (i + ft_strlen(src));
}
