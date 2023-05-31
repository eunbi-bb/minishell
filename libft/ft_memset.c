/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 16:09:28 by eucho         #+#    #+#                 */
/*   Updated: 2022/10/24 15:28:06 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* 
	DESCRIPTION
		memset() copies 'c' to the first 'n' of the string pointed to, 
		by the argument 'str'.
		'c' is the value to set. The value is passed as an int, 
		but the function fills
		the block of memory using the unisgned char conversion of this value.
		'n' is the number of bytes to be set to the value.
	RETURN VALUE
		Returns a pointer to the memory area 'str'.	
*/
#include <stdlib.h>

void	*ft_memset(void *str, int c, size_t n)
{
	char	*ptr;
	size_t	i;

	ptr = str;
	i = 0;
	while (i < n)
	{
		ptr[i] = c;
		i++;
	}
	return (str);
}
