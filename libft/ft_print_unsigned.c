/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_unsigned.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 21:30:35 by eucho         #+#    #+#                 */
/*   Updated: 2022/10/11 21:30:35 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	unsigned_get_len(unsigned int num)
{
	unsigned int	len;

	len = 0;
	while (num)
	{
		num = num / 10;
		len++;
	}
	return (len);
}

char	*ft_unsigned_itoa(unsigned int n)
{
	char			*str;
	unsigned int	len;

	len = unsigned_get_len(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (n)
	{
		str[len - 1] = (n % 10) + '0';
		n = n / 10;
		len--;
	}
	return (str);
}

int	ft_print_unsigned(unsigned int n)
{
	int		len;
	char	*unsigned_num;

	len = 0;
	if (n == 0)
		len = write(1, "0", 1);
	else
	{
		unsigned_num = ft_unsigned_itoa(n);
		len += ft_print_string(unsigned_num);
		free(unsigned_num);
	}
	return (len);
}
