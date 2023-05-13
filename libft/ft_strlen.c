/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 16:11:36 by eucho         #+#    #+#                 */
/*   Updated: 2022/10/24 15:38:43 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
	DESCRIPTION
		strlen() calculates the length of a given string.
	RETURN VALUE
		The length of the given string.
*/
#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}
