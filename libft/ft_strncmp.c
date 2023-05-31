/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 16:12:06 by eucho         #+#    #+#                 */
/*   Updated: 2022/10/24 15:33:37 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
	DESCRIPTION
		strncmp compares the two strings provided up to 'n' characters
		strncmp() will stop comparing if a null character is encountered in 
		either '*s1' or '*s2'.
	RETURN VALUE
		returns a negative, zero, or positive integer depending on 
		whether the first 'n' characters of the object pointed to 
		by '*s1' are less than, equal to, or greater than the first 'n' characters
		of the object pointed to by '*s2'.
*/
#include <stdlib.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && (s1[i] && s2[i]) && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
