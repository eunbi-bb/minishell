/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstdelone.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 16:07:06 by eucho         #+#    #+#                 */
/*   Updated: 2022/10/11 20:21:44 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* 
	DESCRIPTION
		lstdelone() takes as a parameter a node and frees the memory of
		the node's content using the function 'del' given as a parameter
		and free the node. Then memory of 'next' must not be freed.
		'lst' : the node to free.
		'del' : the address of the function used to delete the content.
*/
#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst && del)
	{
		del(lst->content);
		free(lst);
	}
}
