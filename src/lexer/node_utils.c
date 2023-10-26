/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   node_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/20 14:24:46 by eucho         #+#    #+#                 */
/*   Updated: 2023/10/26 09:38:53 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

t_tokens	*new_token_node(char *data, t_types token, char quote)
{
	t_tokens	*new;

	new = ft_calloc(1, sizeof(t_tokens));
	if (!new)
	{
		perror("malloc");
		exit(1);
	}
	if (data == NULL)
		new->data = NULL;
	else
		new->data = ft_strdup(data);
	new->token = token;
	if (quote == '\'')
		new->s_quote = true;
	else if (quote == '\"')
		new->d_quote = true;
	else
	{
		new->s_quote = false;
		new->d_quote = false;
	}
	new->next = NULL;
	return (new);
}

void	add_after(t_tokens **before, t_tokens *new_node)
{
	t_tokens	*head;

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

void	add_to(t_tokens *before, char *data)
{
	before->data = ft_strjoin(before->data, data);
}

void	add_to_last(t_tokens **before, char *data)
{
	t_tokens	*head;

	head = *before;
	if (head == NULL)
	{
		return;
	}
	else
	{
		while (head->next != NULL)
			head = head->next;
		head->data = ft_strjoin(head->data, data);
	}
}
