/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_unset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ssemanco <ssemanco@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 14:32:33 by ssemanco      #+#    #+#                 */
/*   Updated: 2023/10/24 22:11:38 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "error.h"

void	unset_free(t_env *current, t_env *previous)
{
	if (previous == NULL)
		current = current->next;
	else
		previous->next = current->next;
	if (current->key != NULL)
		free(current->key);
	if (current->value != NULL)
		free(current->value);
	free(current);
	current = NULL;
}

void	check_malloc(char *key)
{
	if (!key)
		err_msg("malloc fail");
}

void unset_no_es(t_env *head, char *key)
{
    t_env *current = head;
    t_env *previous = NULL;

    while (current)
    {
        if (ft_strcmp(current->key, key) == 0 && ft_strcmp(current->value, "") == 0)
        {
            if (previous == NULL)
                head = current->next;
            else
                previous->next = current->next;
            free(current->key);
            free(current->value);
            free(current);
            current = NULL;
            return ;
        }
        previous = current;
        current = current->next;
    }
}

int	cmd_unset(t_env *head, char **key)
{
	t_env	*current;
	t_env	*previous;
	char	*key_eq;
	int		i;

	i = 0;
	previous = NULL;
	while (key[++i])
	{
		key_eq = ft_strjoin(key[i], "=");
		check_malloc(key_eq);
		current = head;
		while (current)
		{
			if (strcmp(current->key, key_eq) == 0)
			{
				unset_free(current, previous);
				break ;
			}
			previous = current;
			current = current->next;
		}
		unset_no_es(head, key[i]);
		free(key_eq);
	}
	return (0);
}
