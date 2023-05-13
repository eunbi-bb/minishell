/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   node_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/20 14:24:46 by eucho         #+#    #+#                 */
/*   Updated: 2023/05/13 18:31:33 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*new_node(int data, int size)
{
	t_token	*new_node;

	new_node = malloc(size + 1);
	if (!new_node)
		return (NULL);
	new_node->data = data;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	add_before(t_token *current, t_token *new_node)
{
	t_token	*head;

	head = lst_front(current);
	if (current == NULL)
	{
		current = new_node;
	}
	else if (current == head)
	{
		new_node->prev = NULL;
		new_node->next = current;
		current->prev = new_node;
	}
	else
	{
		new_node->next = current;
		new_node->prev = current->prev;
		current->prev->next = new_node;
		current->prev = new_node;
	}
}

void	add_after(t_token *before, t_token *new_node)
{
	t_token	*head;
	t_token	*tail;

	head = lst_front(before);
	tail = lst_last(before);
	if (before == NULL)
	{
		new_node->next = head;
		if (head)
			head->prev = new_node;
	}
	else if (before == tail)
	{
		new_node->prev = tail;
		tail->next = new_node;
		tail = new_node;
	}
	else
	{
		new_node->prev = before;
		new_node->next = before->next;
		before->next->prev = new_node;
		before->next = new_node;
	}
}

void	del_node(t_token **head, t_token **tail, t_token *p)
{
	if (head == NULL || *head == NULL || p == NULL)
		return ;
	if (p == *head)
	{
		*head = p->next;
		if (*head != NULL)
			(*head)->prev = NULL;
		else
			*tail = NULL;
	}
	else if (p == *tail)
	{
		*tail = p->prev;
		if (*tail != NULL)
			(*tail)->next = NULL;
		else
			*head = NULL;
	}
	else
	{
		p->prev->next = p->next;
		p->next->prev = p->prev;
	}
	free(p);
}
