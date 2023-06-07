#include <stdio.h>
#include <stdlib.h>
typedef	struct	s_tokens
{
	char			*data;
	char				token;
	struct s_tokens	*next;
}	t_tokens;


t_tokens	*new_token_node(char token)
{
	t_tokens	*new;

	new = (t_tokens *)malloc(sizeof(t_tokens));
	if (new == NULL)
	{
		perror("malloc");
		exit(1);
	}
	new->data = NULL;
	new->token = token;
	new->next = NULL;

	return (new);
}

void	add_after(t_tokens **before, t_tokens *new_node)
{
	t_tokens	*head;

	head = *before;//lst_front(before);
	if (head == NULL)
	{
		*before = new_node;
		return ;
	}
	else
	{
		while (head->next != NULL)
			head = head->next;
		head->next = new_node;
	}
}

int main(void)
{
	
	t_tokens *top = NULL;//new_token_node('c');

	add_after(&top,new_token_node('c'));
	add_after(&top,new_token_node('c'));
	add_after(&top,new_token_node('c'));
	int i = 0;
	t_tokens *current = top;
	while(current != NULL)
	{
		printf("current->token:%c",current->token);
		current = current->next;
	}
	return 0;
}