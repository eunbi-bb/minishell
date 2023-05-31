/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 16:08:16 by eucho         #+#    #+#                 */
/*   Updated: 2022/10/11 20:12:56 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* 
	DESCRIPTION
		lstnew() allocates and returns a new node. The member variable 'content'
		is initialized with the value of the parameter 'content'.
		The variable 'next' is initialized to NULL.
		'content' : the content to create the node with.
	RETURN VALUE
		The new node. 
*/
#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*lst;

	lst = malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	lst->content = content;
	lst->next = NULL;
	return (lst);
}
