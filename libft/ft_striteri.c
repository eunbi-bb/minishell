/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_striteri.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 16:11:03 by eucho         #+#    #+#                 */
/*   Updated: 2022/10/10 16:11:06 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* 
	DESCRIPTION
		void(*f)() : a pointer variable that has the address of function.
					Function is a type of address so it's be able to use as normal pointer.
				Summary = No return value, function pointer.
				useful to read big amount of data.
		striteri itinerates '*s' and apply '*f' to every elements.
*/
#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	len;
	int	i;

	i = 0;
	if (s && f)
	{
		len = ft_strlen(s);
		while (i < len)
		{
			f(i, s + i);
			i++;
		}
	}
}
