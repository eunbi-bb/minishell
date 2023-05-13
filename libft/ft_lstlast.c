/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstlast.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 16:07:43 by eucho         #+#    #+#                 */
/*   Updated: 2022/10/16 20:54:23 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* 
	DESCRIPTION
		lstlast() returns the last node of the list.
		'lst' : the begining of the list.
	RETURN VALUE
		The last node of the list.
*/
#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
