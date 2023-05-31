/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 16:11:26 by eucho         #+#    #+#                 */
/*   Updated: 2022/12/21 14:03:41 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* 
	DESCRIPTION
		strlcpy() takes the full size of the buffer, not only the length,
		and terminates the result with NUL as long as is greater than 0. 
		Include a byte for the NUL in your value.
	RETURN VALUE
		returns the total length of the string that would have been copied 
		if there was unlimited space.
		This might or might not be equal to the length 
		of the string actually copied, depending on whether there was enough space.
		This means that you can call strlcpy() once to find out how much space 
		is required, then allocate it if you do not have enough, 
		and finally call strlcpy() a second time to do the required copy.
*/
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(src);
	if (size > 0)
	{
		while (i < len && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (len);
}
