#include <stdlib.h>
#include "../includes/minishell.h"

void free_tokens_list(t_tokens *head)
{
	t_tokens	*tmp;

    while (head)
    {
        tmp = head;
        head = head->next;
        if (tmp->data)
            free(tmp->data);
        free(tmp);
    }
}