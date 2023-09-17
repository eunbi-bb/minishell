#include <stdlib.h>
#include "../includes/minishell.h"

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

void	free_lexer_nodes(t_tokens *head)
{
	t_tokens *current;
	t_tokens *tmp;

	current = head;
	while (current != NULL)
	{
		tmp = current;
		current = current->next;
		free(tmp);
	}
}

void	destroy_lexer_list(t_tokens **head_ref)
{
	free_lexer_nodes(*head_ref);
	*head_ref = NULL;
}

void	free_parser_nodes(t_cmd *head)
{
	t_cmd *current;
	t_cmd *tmp;

	current = head;
	while (current != NULL)
	{
		tmp = current;
		current = current->next;
		free(tmp);
	}
}

void	destroy_parser_list(t_cmd **head_ref)
{
	free_parser_nodes(*head_ref);
	*head_ref = NULL;
}
