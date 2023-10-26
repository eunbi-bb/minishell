/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ssemanco <ssemanco@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/18 19:33:20 by ssemanco      #+#    #+#                 */
/*   Updated: 2023/10/22 15:36:33 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "error.h"

char	*search_value(char *key, t_env *env)
{
	size_t	len;
	char	*empty;

	empty = NULL;
	len = ft_strlen(key);
	while (env)
	{
		if (ft_strncmp(key, env->key, len) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	empty = ft_strdup("");
	return (empty);
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
	char		*key;

	current = token_list;
	val = NULL;
	while (current != NULL)
	{
		if (current->token == QUESTION && current->s_quote == false)
			current->data = print_qm(current->data);
		if (current->token == DOLLAR && current->s_quote == false)
		{
			key = ft_strjoin(current->data + 1, "=");
			if (!key)
				err_msg("Malloc\n");
			val = search_value(key, env);
			free(key);
			replace_val(current, val);
		}
		current = current->next;
	}
}
