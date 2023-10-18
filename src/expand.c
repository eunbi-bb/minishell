/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ssemanco <ssemanco@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/18 19:33:20 by ssemanco      #+#    #+#                 */
/*   Updated: 2023/10/18 19:36:05 by ssemanco      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_value(char *key, t_env *env)
{
	size_t	len;

	len = ft_strlen(key);
	while (env)
	{
		if (ft_strncmp(key, env->key, len) == 0)
			return (env->value);
		env = env->next;
	}
	return (ft_strdup(""));
}

char	*print_qm(char *data)
{
	char	*exitc;

	exitc = ft_itoa(g_exit_status);
	free(data);
	data = ft_strdup(exitc);
	free(exitc);
	return (data);
}

void	replace_val(t_tokens *current, char *val)
{
	free(current->data);
	current->data = ft_strdup(val);
	free(val);
}

void	expand(t_tokens *token_list, t_env *env)
{
	t_tokens	*current;
	char		*val;
	size_t		len;
	char		*key;

	current = token_list;
	while (current != NULL)
	{
		if (current->token == QUESTION && current->s_quote == false)
			current->data = print_qm(current->data);
		if (current->token == DOLLAR && current->s_quote == false)
		{
			key = ft_strjoin(current->data + 1, "=");
			len = ft_strlen(key);
			if (len > 1)
			{
				val = search_value(key, env);
				free(key);
				if (val)
					replace_val(current, val);
			}
		}
		current = current->next;
	}
}
