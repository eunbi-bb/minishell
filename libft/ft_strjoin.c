/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 16:11:10 by eucho         #+#    #+#                 */
/*   Updated: 2023/02/25 15:59:12 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* 
	DESCRIPTION
		strjoin() constructs string by linking '*s1' in '*s2'.
	RETURN VALUE
		A pointer of the joined string.
*/
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	len_1;
	unsigned int	len_2;
	char			*str;

	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (len_1 + len_2 + 1));
	if (!str)
		return (NULL);
	ft_memcpy(str, (char *)s1, len_1);
	ft_memcpy(str + len_1, (char *)s2, len_2);
	str[len_1 + len_2] = '\0';
	return (str);
}
