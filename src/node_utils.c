/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   node_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/20 14:24:46 by eucho         #+#    #+#                 */
/*   Updated: 2023/05/29 13:54:34 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

t_tokens	*lst_last(t_tokens *lst)
{
	t_tokens	*tmp;

	tmp = lst;
	if (!tmp)
		return (tmp);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_tokens	*lst_front(t_tokens *lst)
{
	t_tokens	*tmp;

	tmp = lst;
	if (!tmp)
		return (tmp);
	while (tmp->prev)
		tmp = tmp->prev;
	return (tmp);
}

t_tokens	*new_node(char *data, int size)
{
	t_tokens	*new_node;

	new_node = malloc(size + 1);
	if (!new_node)
		return (NULL);
	new_node->data = data;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

t_tokens	*new_token_node(char token)
{
	t_tokens	*new_node;

	new_node = malloc((sizeof(char) * 1));
	if (!new_node)
		return (NULL);
	new_node->token = token;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	add_before(t_tokens *current, t_tokens *new_node)
{
	t_tokens	*head;

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

void	add_after(t_tokens *before, t_tokens *new_node)
{
	t_tokens	*head;
	t_tokens	*tail;

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

void	del_node(t_tokens **head, t_tokens **tail, t_tokens *p)
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
