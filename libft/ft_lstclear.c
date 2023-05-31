/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 16:06:51 by eucho         #+#    #+#                 */
/*   Updated: 2022/10/11 20:15:31 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
	DESCRIPTION
		lstclear() deletes and fress the fiven node and every successor of
		that node, using the function 'del' and free().
		Finally, the pointer to the list must be set to NULL.
		lst() : the address of a pointer to a node.
		del() : the address of the function used to delete the content of the node.
*/
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (lst && del)
	{
		while (*lst)
		{
			tmp = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = tmp;
		}
	}
}
