/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 16:10:16 by eucho         #+#    #+#                 */
/*   Updated: 2023/10/22 11:56:37 by ssemanco      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* 
	DESCRIPTION
		strcmp() compares two strings character by character.
	RETURN VALUE
		Returns 0 if the strings are equal.
		Returns positive if s1 > s2
		Returns negative if s1 < s2
*/
#include <stdlib.h>

int	ft_strcmp(const char *str1, const char *str2)
{
	while (*str1 != '\0' || *str2 != '\0')
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	return (0);
}
