/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_unset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ssemanco <ssemanco@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 14:32:33 by ssemanco      #+#    #+#                 */
/*   Updated: 2023/09/23 18:13:32 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "error.h"

void	unset_free(t_env *current, t_env *previous, t_env **head, char *key_eq)
{
	if (previous == NULL)
		*head = current->next;
	else
		previous->next = current->next;
	free(current->key);
	free(current->value);
	free(current);
	free(key_eq);
}

int	cmd_unset(t_env **head, char **key)
{
	t_env	*current;
	t_env	*previous;
	char	*key_eq;
	int		i;

	previous = NULL;
	i = 1;
	while (key[i])
	{
		current = *head;
		while (current)
		{
			key_eq = ft_strjoin(key[i], "=");
			if (!key_eq)
				err_msg("malloc fail");
			if (strcmp(current->key, key_eq) == 0)
				unset_free(current, previous, head, key_eq);
			else
				previous = current;
			current = current->next;
		}
		i++;
	}
	return (0);
}
