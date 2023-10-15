/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_export.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ssemanco <ssemanco@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 15:38:07 by ssemanco      #+#    #+#                 */
/*   Updated: 2023/10/15 18:35:30 by ssemanco      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "error.h"

void	unset_var(t_env **head, char *key)
{
	t_env	*current;
	t_env	*previous;

	current = *head;
	previous = NULL;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (previous == NULL)
				*head = current->next;
			else
				previous->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		previous = current;
		current = current->next;
	}
}

t_env	*insert_node(char *str, t_env **head)
{
	char	*eq_s;
	size_t	key_len;
	t_env	*new_node;
	t_env	*current;

	current = *head;
	new_node = (t_env *)malloc(sizeof(t_env));
	if (new_node == NULL)
	{
		perror("malloc");
		exit(1);
	}
	eq_s = ft_strchr(str, '=');
	if (eq_s == NULL)
		return (NULL);
	key_len = eq_s - str + 1;
	new_node->key = ft_substr(str, 0, key_len);
	if (var_exist(new_node->key, current) == 0)
		unset_var(head, new_node->key);
	new_node->value = ft_strdup(eq_s + 1);
	new_node->next = NULL;
	return (new_node);
}

int	valid_char(char *str)
{
	if (ft_isdigit(str[0]))
		return (1);
	if (ft_strchr(str, '-'))
		return (1);
	return (0);
}

void	add_to_list(t_env *current, t_env **head, char *str)
{
	t_env	*new_node;

	new_node = insert_node(str, head);
	if (*head == NULL)
		*head = new_node;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}

int	cmd_export(t_env **head, char **str)
{
	t_env	*current;
	t_env	*sorted;
	int		i;

	i = 1;
	current = NULL;
	if (!str[1])
	{
		sorted = merge_sort(*head);
		print_list(sorted);
	}
	else
	{
		while (str[i])
		{
			if (valid_char(str[i]) == 1)
			{
				printf("export: '%s': not a valid identifier\n", str[i]);
				return (1);
			}
			add_to_list(current, head, str[i]);
			i++;
		}
	}
	return (0);
}
