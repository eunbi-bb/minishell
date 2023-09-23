#include <stdlib.h>
#include "minishell.h"

// void free_tokens_list(t_tokens *head)
// {
// 	t_tokens	*tmp;

//     while (head)
//     {
//         tmp = head;
//         head = head->next;
//         if (tmp->data)
//             free(tmp->data);
//         free(tmp);
//     }
// }

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
