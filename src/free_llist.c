#include <stdlib.h>
#include "minishell.h"


void	reset_lexer_parser(t_lexer_utils *lexer, t_parser_utils *parser)
{
	destroy_lexer_list(&(lexer->token_list));
	destroy_parser_list(&(parser->cmd_list));
	if (lexer->arg)
		free(lexer->arg);
	// if (lexer->type_arr)
	// 	free(lexer->type_arr);
	// if (lexer->heredoc_filename)
	// 	free(lexer->heredoc_filename);
	// if (parser->args)
	// 	free(parser->args);
	// if (parser->command)
	// 	free(parser->command);
}

void	destory_utils(t_lexer_utils *lexer, t_parser_utils *parser)
{
	int	i;

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
}

void	destroy_lexer_list(t_tokens **head_ref)
{
    t_tokens *current;
    t_tokens *tmp;

	current = *head_ref;
    while (current != NULL)
    {
        tmp = current;
		if (current->data != NULL)
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
		if (current->key != NULL)
        	free(current->key);
		if (current->value != NULL)
        	free(current->value);
		current = current->next;
        free(tmp);
    }
	*head_ref = NULL;
}
