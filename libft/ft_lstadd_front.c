/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_front.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 16:06:29 by eucho         #+#    #+#                 */
/*   Updated: 2022/10/11 08:58:12 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* 
	DESCRIPTION
		lstadd_front() adds the node 'new' at the beginning of the list.
		'lst' : the address of a pointer to the first link of a list.
		'new' : the address of a pointer to the node to be added to the list.
*/
#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}
