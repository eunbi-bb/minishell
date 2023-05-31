/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalnum.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 16:03:32 by eucho         #+#    #+#                 */
/*   Updated: 2022/10/10 16:15:50 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
	DESCPIPTION
		isalnum() tests for any character for which isalpha 
		or isdigit is true.
	RETURN VALUE
		It returns 0 if the character tests false. Otherwise non-zero 
		if the tests is true.
*/
#include "libft.h"

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}
