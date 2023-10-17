/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir_node_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 16:12:49 by eucho         #+#    #+#                 */
/*   Updated: 2023/10/16 23:41:21 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_after_redir(t_redir **before, t_redir *new_node)
{
	t_redir	*head;

	head = *before;
	if (head == NULL)
	{
		*before = new_node;
		new_node->prev = NULL;
		new_node->next = NULL;
	}
	else
	{
		while (head->next != NULL)
			head = head->next;
		head->next = new_node;
		new_node->prev = head;
		new_node->next = NULL;
	}
}

t_redir	*create_redir_node(void)
{
	t_redir	*redir;

	redir = ft_calloc(1, sizeof(t_redir));
	redir->file_name = NULL;
	redir->redir_type = DEFAULT;
	redir->prev = NULL;
	redir->next = NULL;
	return (redir);
}
