/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_llist.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 16:10:50 by eucho         #+#    #+#                 */
/*   Updated: 2023/10/15 00:27:29 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

void	reset(t_lexer_utils *lexer, t_parser_utils *parser, char *line)
{
	free_token_list(lexer);
	free_cmd_list(parser);
	free(line);
	lexer->pipe_num = 0;
}

void	free_token_list(t_lexer_utils *lexer)
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
	t_redir	*tmp;

	while (cmd->redir)
	{
		tmp = cmd->redir;
		cmd->redir = cmd->redir->next;
		if (tmp->file_name)
		{
			free(tmp->file_name);
		}
		free(tmp);
	}
}

void	free_cmd_list(t_parser_utils *parser)
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

void	free_env_list(t_parser_utils *parser)
{
	t_env	*env_list;
	t_env	*tmp;
	int		i;

	i = 0;
	while (parser->env[i])
	{
		env_list = parser->env[i];
		while (env_list)
		{
			tmp = env_list;
			env_list = env_list->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
		}
		i++;
	}
	free(parser->env);
}

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

void	destroy_parser_utils(t_parser_utils *parser)
{
	int	i;

	free_cmd_list(parser);
	free(parser->args);
	free_env_list(parser);
	free_envp(parser->envp);
	i = 0;
	while (parser->cmd_dirs[i])
	{
		free(parser->cmd_dirs[i]);
		i++;
	}
	free(parser->cmd_dirs);
	free(parser->command);
}

void	destroy_lexer_utils(t_lexer_utils *lexer)
{
	free_token_list(lexer);
	free(lexer->type_arr);
}
