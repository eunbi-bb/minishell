/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 16:12:19 by eucho         #+#    #+#                 */
/*   Updated: 2022/10/17 13:50:49 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
	DESCRIPTION
		strrchr() searches for the last occurrence of 'c' in the string 
		pointed to, by the argument '*s'.
	RETURN VALUE
		returns a pointer to the last occurrence of character in '*s'. 
		If the value is not found, the function returns NULL.
*/
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s) + 1;
	while (i > 0)
	{
		i--;
		if (s[i] == (char)c)
			return (&((char *)s)[i]);
	}
	return (NULL);
}
