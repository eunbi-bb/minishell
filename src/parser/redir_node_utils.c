#include "../../includes/minishell.h"

void	add_after_redir(t_redir **before, t_redir *new_node)
{
	t_redir	*head;

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

t_redir	*create_redir_node(void)
{
	t_redir	*redir;

	redir = ft_calloc(1, sizeof(t_redir));
	redir->file_name = NULL;
	redir->redir_type = DEFAULT;
	redir->next = NULL;
	return (redir); 
}