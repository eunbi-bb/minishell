/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 16:05:38 by eucho         #+#    #+#                 */
/*   Updated: 2022/10/25 11:40:05 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
	DESCRIPTION
		Integer to Character. Dividing interger to get a length for a string.
		
	RETURN VALUE
		returns converted string. 
*/
#include "libft.h"
#include <stdlib.h>

static int	get_len(int n)
{
	int	len;

	if (n <= 0)
		len = 1;
	else
		len = 0;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;
	int		num;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = get_len(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n < 0)
		num = -n;
	else
		num = n;
	len--;
	while (len >= 0)
	{
		str[len] = '0' + (num % 10);
		num = num / 10;
		len--;
	}
	if (n < 0 && n != -2147483648)
		str[0] = '-';
	return (str);
}
