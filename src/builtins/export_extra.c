/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_extra.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ssemanco <ssemanco@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/18 21:31:54 by ssemanco      #+#    #+#                 */
/*   Updated: 2023/10/29 16:48:42 by ssemanco      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "error.h"

void	free_sorted(t_env *head)
{
	t_env	*current;
	t_env	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		if (current->key)
			free(current->key);
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
}

int	valid_char(char *str)
{
	if (ft_isdigit(str[0]))
		return (1);
	if (ft_strchr(str, '-'))
		return (1);
	if (str[0] == '=')
		return (1);
	return (0);
}

void	free_double(char *key, char *value, t_env *current, char *str)
{
	free(key);
	free(value);
	free(current);
	free(str);
}

void	unset_var(t_env *head, char *key)
{
	t_env	*current;
	t_env	*previous;
	char	*str;

	current = head;
	previous = NULL;
	while (current != NULL)
	{
		str = ft_strtrim(key, "=");
		if (ft_strcmp(current->key, str) == 0)
		{
			if (previous == NULL)
				head = current->next;
			else
				previous->next = current->next;
			free_double(current->key, current->value, current, str);
			return ;
		}
		if (str)
			free(str);
		previous = current;
		current = current->next;
	}
}

t_env	*insert_node(char *str, t_env *head)
{
	char	*eq_s;
	size_t	key_len;
	t_env	*new_node;
	t_env	*current;

	current = head;
	new_node = (t_env *)malloc(sizeof(t_env));
	if (new_node == NULL)
		perror_exit("malloc fail");
	eq_s = ft_strchr(str, '=');
	if (eq_s == NULL)
	{
		new_node->key = ft_substr(str, 0, ft_strlen(str));
		new_node->value = ft_strdup("");
	}
	else
	{
		key_len = eq_s - str + 1;
		new_node->key = ft_substr(str, 0, key_len);
		if (var_exist(new_node->key, current) == 0)
			unset_var(head, new_node->key);
		new_node->value = ft_strdup(eq_s + 1);
	}
	new_node->next = NULL;
	return (new_node);
}
