/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_export.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ssemanco <ssemanco@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 15:38:07 by ssemanco      #+#    #+#                 */
/*   Updated: 2023/10/29 16:02:40 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "error.h"

void	add_to_list(t_env *current, t_env *head, char *str)
{
	t_env	*new_node;

	new_node = insert_node(str, head);
	if (head == NULL)
		head = new_node;
	else
	{
		current = head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}

t_env	*create_node(char *key, char *value)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (new_node)
	{
		new_node->key = ft_strdup(key);
		new_node->value = ft_strdup(value);
		new_node->next = NULL;
	}
	return (new_node);
}

t_env	*copy_env_list(t_env *source)
{
	t_env	*head;
	t_env	*tail;
	t_env	*new_node;

	head = NULL;
	tail = NULL;
	while (source)
	{
		new_node = create_node(source->key, source->value);
		if (new_node)
		{
			if (!head)
			{
				head = new_node;
				tail = new_node;
			}
			else
			{
				tail->next = new_node;
				tail = new_node;
			}
		}
		source = source->next;
	}
	return (head);
}

int	cmd_export(t_env *head, t_env *sorted, char **str)
{
	t_env	*current;
	int		i;

	i = 1;
	current = NULL;
	sorted = copy_env_list(head);
	if (!str[1])
		sorted = merge_sort(sorted);
	else
	{
		while (str[i])
		{
			if (valid_char(str[i]) == 1)
			{
				printf("export: '%s': not a valid identifier\n", str[i]);
				free_sorted(sorted);
				return (1);
			}
			add_to_list(current, head, str[i]);
			i++;
		}
	}
	free_sorted(sorted);
	return (0);
}
