#include <stdlib.h>
#include "minishell.h"


void	reset_lexer_parser(t_lexer_utils *lexer, t_parser_utils *parser)
{
	destroy_lexer_list(&(lexer->token_list));
	destroy_parser_list(&(parser->cmd_list));
	// if (lexer->arg)
	// 	free(lexer->arg);
	lexer->pipe_num = 0;
	lexer->heredoc = false;
	// if (lexer->type_arr)
	// 	free(lexer->type_arr);
	// if (parser->args)
	// 	free(parser->args);
	// if (parser->command)
	// 	free(parser->command);
}

void	destory_utils(t_lexer_utils *lexer, t_parser_utils *parser)
{
	int	i;
	(void)lexer;

	reset_lexer_parser(lexer, parser);
	destroy_env_list(parser->env);
	i = 0;
	if (parser->cmd_dirs)
	{
		while (parser->cmd_dirs[i])
		{
			free(parser->cmd_dirs[i]);
			i++;
		}
		free(parser->cmd_dirs);
		parser->cmd_dirs = NULL;
	}
	i = 0;
	if (parser->envp)
	{
		while (parser->envp[i])
		{
			free(parser->envp[i]);
			i++;
		}
		free(parser->envp);
		parser->envp = NULL;
	}
}

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

void	destroy_parser_utils(t_parser_utils *parser)
{
	int	i;
	free_cmd_list(parser);
	free(parser->args);
	free_env_list(parser);
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

/*********************************************/
void	destroy_lexer_list(t_tokens **head_ref)
{
    t_tokens *current;
    t_tokens *tmp;

	current = *head_ref;
    while (current != NULL)
    {
        tmp = current;
		if (current->data)
			free(current->data);
        current = current->next;
        free(tmp);
    }
    *head_ref = NULL;
}

void	destroy_redir_list(t_redir **head_ref)
{
	t_redir *current;
    t_redir *tmp;

	current = *head_ref;
    while (current != NULL)
    {
        tmp = current;
		if (current->file_name != NULL)
			free(current->file_name);
        current = current->next;
        free(tmp);
    }
    *head_ref = NULL;
}

void	destroy_parser_list(t_cmd **head_ref)
{
	t_cmd *current;
	t_cmd *tmp;

	current = *head_ref;
	while (current != NULL)
	{
		tmp = current;
		if (current->data != NULL)
			free(current->data);
		destroy_redir_list(&current->redir);
		current = current->next;
		free(tmp);
	}
	*head_ref = NULL;
}

void destroy_env_list(t_env **head_ref)
{
	t_env	*current;
	t_env	*tmp;

	current = *head_ref;
    while (current != NULL)
    {
        tmp = current;
		if (current->key)
        	free(current->key);
		if (current->value)
        	free(current->value);
		current = current->next;
        free(tmp);
    }
	*head_ref = NULL;
}
