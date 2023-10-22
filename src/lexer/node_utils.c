/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   node_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/20 14:24:46 by eucho         #+#    #+#                 */
/*   Updated: 2023/10/22 15:56:17 by eucho         ########   odam.nl         */
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
