/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstiter.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 16:07:28 by eucho         #+#    #+#                 */
/*   Updated: 2022/10/11 09:12:55 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* 
	DESCRIPTION
		Iterates the list 'lst' and applies the function 'f' on the content 
		of each node.
		'lst'	: the address of a pointer to a node.
		'f'		: the adress of the function used to iterate on the list.
*/
#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
