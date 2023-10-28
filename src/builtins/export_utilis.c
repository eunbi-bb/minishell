/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_utilis.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ssemanco <ssemanco@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/15 14:50:56 by ssemanco      #+#    #+#                 */
/*   Updated: 2023/10/29 00:19:23 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "error.h"

// Function to split the linked list into two halves
void	split_list(t_env *source, t_env **left_ref, t_env **right_ref)
{
	t_env	*fast;
	t_env	*slow;

	if (source == NULL || source->next == NULL)
	{
		*left_ref = source;
		*right_ref = NULL;
	}
	else
	{
		slow = source;
		fast = source->next;
		while (fast != NULL)
		{
			fast = fast->next;
			if (fast != NULL)
			{
				slow = slow->next;
				fast = fast->next;
			}
		}
		*left_ref = source;
		*right_ref = slow->next;
		slow->next = NULL;
	}
}

t_env	*merge(t_env *left, t_env *right)
{
	t_env	*result;

	result = NULL;
	if (left == NULL)
		return (right);
	if (right == NULL)
		return (left);
	if (ft_strcmp(left->key, right->key) <= 0)
	{
		result = left;
		result->next = merge(left->next, right);
	}
	else
	{
		result = right;
		result->next = merge(left, right->next);
	}
	return (result);
}

// Merge Sort function for sorting the linked list
t_env	*merge_sort(t_env *head)
{
	t_env	*left;
	t_env	*right;
	t_env	*sorted;

	if (head == NULL || head->next == NULL)
		return (head);
	split_list(head, &left, &right);
	left = merge_sort(left);
	right = merge_sort(right);
	sorted = merge(left, right);
	return (sorted);
}

int	var_exist(char *key, t_env *env)
{
	size_t	len;

	len = ft_strlen(key);
	while (env)
	{
		if (ft_strncmp(key, env->key, len) == 0)
			return (0);
		env = env->next;
	}
	return (1);
}

void	print_list(t_env *head)
{
	t_env	*current;

	current = head;
	while (current != NULL)
	{
		printf("declare -x %s%s\n", current->key, current->value);
		current = current->next;
	}
}
