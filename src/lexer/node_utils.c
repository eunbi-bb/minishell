/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   node_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/20 14:24:46 by eucho         #+#    #+#                 */
/*   Updated: 2023/09/25 23:00:23 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

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

t_tokens	*new_node(char *data)
{
	t_tokens	*new_node;

	new_node = ft_calloc(1, sizeof(t_tokens));
	if (!new_node)
		return (NULL);
	new_node->data = ft_strdup(data);
	new_node->token = DEFAULT;
	new_node->next = NULL;
	return (new_node);
}

t_tokens	*new_token_node(t_types token)
{
	t_tokens	*new;

	new = ft_calloc(1, sizeof(t_tokens));
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
	}
	else
	{
		while (head->next != NULL)
			head = head->next;
		head->next = new_node;
	}
}
