/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   node_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/20 14:24:46 by eucho         #+#    #+#                 */
/*   Updated: 2023/06/07 18:34:57 by eucho         ########   odam.nl         */
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

// t_tokens	*lst_front(t_tokens *lst)
// {
// 	t_tokens	*tmp;

// 	tmp = lst;
// 	if (!tmp)
// 		return (tmp);
// 	while (tmp->prev)
// 		tmp = tmp->prev;
// 	return (tmp);
// }

t_tokens	*new_node(char *data)
{
	t_tokens	*new_node;

	new_node = (t_tokens *)malloc(sizeof(t_tokens));
	if (!new_node)
		return (NULL);
	new_node->data = data;
	new_node->token = -1;
	new_node->next = NULL;
	return (new_node);
}

// t_tokens	*new_token_node(char token)
// {
// 	t_tokens	*new_node;

// 	new_node = (t_tokens *)malloc(sizeof(t_tokens));
// 	if (!new_node)
// 		exit(-1);
// 	new_node->token = token;
// 	new_node->prev = NULL;
// 	new_node->next = NULL;
// 	return (new_node);
// }

// void	add_before(t_tokens *current, t_tokens *new_node)
// {
// 	t_tokens	*head;

// 	head = lst_front(current);
// 	if (current == NULL)
// 	{
// 		current = new_node;
// 	}
// 	else if (current == head)
// 	{
// 		new_node->next = current;
// 		current->prev = new_node;
// 	}
// 	else
// 	{
// 		new_node->next = current;
// 		new_node->prev = current->prev;
// 		current->prev->next = new_node;
// 		current->prev = new_node;
// 	}
// }

t_tokens	*new_token_node(char token)
{
	t_tokens	*new;

	new = (t_tokens *)malloc(sizeof(t_tokens));
	if (new == NULL)
	{
		perror("malloc");
		exit(1);
	}
	new->data = NULL;
	new->token = token;
	new->next = NULL;

	return (new);
}

void	add_after(t_tokens **before, t_tokens *new_node)
{
	t_tokens	*head;

	head = *before;//lst_front(before);
	if (head == NULL)
	{
		*before = new_node;
		return ;
	}
	else
	{
		while (head->next != NULL)
			head = head->next;
		head->next = new_node;
	}
}

// void	del_node(t_tokens **head, t_tokens **tail, t_tokens *p)
// {
// 	if (head == NULL || *head == NULL || p == NULL)
// 		return ;
// 	if (p == *head)
// 	{
// 		*head = p->next;
// 		if (*head != NULL)
// 			(*head)->prev = NULL;
// 		else
// 			*tail = NULL;
// 	}
// 	else if (p == *tail)
// 	{
// 		*tail = p->prev;
// 		if (*tail != NULL)
// 			(*tail)->next = NULL;
// 		else
// 			*head = NULL;
// 	}
// 	else
// 	{
// 		p->prev->next = p->next;
// 		p->next->prev = p->prev;
// 	}
// 	free(p);
// }
