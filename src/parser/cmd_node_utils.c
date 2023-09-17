#include "../../includes/minishell.h"

t_cmd	*cmd_lst_front(t_cmd *lst)
{
	t_cmd	*tmp;

	tmp = lst;
	if (!tmp)
		return (tmp);
	while (tmp->prev)
		tmp = tmp->prev;
	return (tmp);
}

t_cmd	*cmd_lst_last(t_cmd *lst)
{
	t_cmd	*tmp;

	tmp = lst;
	if (!tmp)
		return (tmp);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	add_after_cmd(t_cmd *before, t_cmd *new_node)
{
	t_cmd	*head;
	t_cmd	*tail;

	head = cmd_lst_front(before);
	tail = cmd_lst_last(before);
	if (before == NULL)
	{
		new_node->next = head;
		if (head)
			head->prev = new_node;
	}
	else if (before == tail)
	{
		new_node->prev = tail;
		tail->next = new_node;
		tail = new_node;
	}
	else
	{
		new_node->prev = before;
		new_node->next = before->next;
		before->next->prev = new_node;
		before->next = new_node;
	}
}

t_cmd	*create_cmd_node(void)
{
	t_cmd	*new;

	new = ft_calloc(1, sizeof(t_cmd));
	new->data = NULL;
	new->prev = NULL;
	new->next = NULL;
	return (new); 
}
