/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_llist.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 16:10:50 by eucho         #+#    #+#                 */
/*   Updated: 2023/10/28 23:06:17 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

void	free_token_list(t_lexer *lexer)
{
	t_tokens	*tmp;

	while (lexer->token_list)
	{
		tmp = lexer->token_list;
		lexer->token_list = lexer->token_list->next;
		if (tmp->data)
			free(tmp->data);
		free(tmp);
	}
}

void	free_redir_list(t_cmd *cmd)
{
	t_redir	*current;
	t_redir	*next;

	current = cmd->redir;
	while (current)
	{
		next = current->next;
		if (current->file_name)
			free(current->file_name);
		free(current);
		current = next;
	}
	cmd->redir = NULL;
}

void	free_cmd_list(t_parser *parser)
{
	t_cmd	*tmp;
	int		i;

	while (parser->cmd_list)
	{
		tmp = parser->cmd_list;
		parser->cmd_list = parser->cmd_list->next;
		if (tmp->redir)
		{
			free_redir_list(tmp);
		}
		i = 0;
		if (tmp->data)
		{
			while (tmp->data[i])
			{
				free(tmp->data[i]);
				i++;
			}
			free(tmp->data);
		}
		free(tmp);
	}
}

void	free_env_list(t_parser *parser)
{
	t_env	*tmp;

	while (parser->env)
	{
		tmp = parser->env;
		parser->env = parser->env->next;
		if (tmp->key)
			free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}
