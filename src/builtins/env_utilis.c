/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_utilis.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ssemanco <ssemanco@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/18 13:25:00 by ssemanco      #+#    #+#                 */
/*   Updated: 2023/10/24 22:02:07 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "error.h"

char	**free_array(char **str, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

int	count_env_llist(t_env *head)
{
	int		i;
	t_env	*current;

	i = 0;
	current = head;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i + 1);
}

char	**join_key_value(t_env *head)
{
	char	**str;
	int		i;
	t_env	*current;

	str = (char **)ft_calloc(count_env_llist(head), sizeof(char *));
	if (!str)
		perror_exit("Malloc");
	current = head;
	i = 0;
	while (current)
	{
		str[i] = ft_strjoin(current->key, current->value);
		if (!str[i])
			return (free_array(str, i + 1));
		i++;
		current = current->next;
	}
	str[i] = NULL;
	return (str);
}
