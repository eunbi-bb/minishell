/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 21:30:39 by eucho         #+#    #+#                 */
/*   Updated: 2022/10/11 21:30:39 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_formats(va_list ap, const char format)
{
	int	len;

	len = 0;
	if (format == 'c')
		len += ft_print_char(va_arg(ap, int));
	else if (format == 's')
		len += len + ft_print_string(va_arg(ap, char *));
	else if (format == 'p')
		len += len + ft_print_pointer(va_arg(ap, uintptr_t));
	else if (format == 'd' || format == 'i')
		len += len + ft_print_number(va_arg(ap, int));
	else if (format == 'u')
		len += ft_print_unsigned(va_arg(ap, unsigned int));
	else if (format == 'x' || format == 'X')
		len += ft_print_hex(va_arg(ap, unsigned int), format);
	else if (format == '%')
		len += ft_print_percent();
	else
		len += ft_print_char(format);
	return (len);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		len;
	int		i;

	len = 0;
	i = 0;
	va_start (ap, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			len += ft_formats (ap, str[i + 1]);
			i++;
		}
		else
		{
			len += ft_print_char (str[i]);
		}
		i++;
	}
	va_end (ap);
	return (len);
}
