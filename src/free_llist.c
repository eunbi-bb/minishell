#include <stdlib.h>
#include "minishell.h"


void	free_token_list(t_lexer_utils *lexer)
{
	while (lexer->token_list)
	{
		t_tokens *tmp = lexer->token_list;
		lexer->token_list = lexer->token_list->next;
		free(tmp->data);
		free(tmp);
	}
}

void	free_redir_list(t_cmd *cmd)
{
	while (cmd->redir)
	{
		t_redir *tmp = cmd->redir;
		cmd->redir = cmd->redir->next;
		free(tmp->file_name);
		free(tmp);
	}
}

void	free_cmd_list(t_parser_utils *parser)
{
	int	i;

	while (parser->cmd_list)
	{
		t_cmd *tmp = parser->cmd_list;
		parser->cmd_list = parser->cmd_list->next;
		free_redir_list(tmp);
		i = 0;
		while (tmp->data[i])
		{
			free(tmp->data[i]);
			i++;
		}
		free(tmp->data);
		free(tmp);
	}
}

void	free_env_list(t_parser_utils *parser)
{
	int	i;

	i = 0;
	while (parser->env[i])
	{
		t_env *env_list = parser->env[i];
		while (env_list)
		{
			t_env *tmp = env_list;
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
	int i;

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


