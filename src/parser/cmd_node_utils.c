/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_node_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 16:12:30 by eucho         #+#    #+#                 */
/*   Updated: 2023/10/02 16:19:05 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_after_cmd(t_cmd **before, t_cmd *new_node)
{
	t_cmd	*head;

	head = *before;
	if (head == NULL)
	{
		*before = new_node;
	}
	else
	{
		while (head->next != NULL)
			head = head->next;
		head->next = new_node;
	}
}

t_cmd	*create_cmd_node(void)
{
	t_cmd	*new;

	new = ft_calloc(1, sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->data = NULL;
	new->redir = NULL;
	new->next = NULL;
	return (new);
}
