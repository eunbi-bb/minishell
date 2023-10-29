/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ssemanco <ssemanco@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/18 19:33:20 by ssemanco      #+#    #+#                 */
/*   Updated: 2023/10/29 13:31:21 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "error.h"

char	*search_value(char *key, t_env *env)
{
	t_env	*curr;
	size_t	len;
	char	*empty;

	empty = NULL;
	len = ft_strlen(key);
	curr = env;
	while (curr)
	{
		if (ft_strncmp(key, curr->key, len) == 0)
			return (curr->value);
		curr = curr->next;
	}
	empty = ft_strdup("");
	return (empty);
}

char	*expand(char *str, t_env *env)
{
	char	*key;
	int		i;
	char	*out;
	char	*exit_code;

	out = NULL;
	exit_code = NULL;
	i = 0;
	if (str[i + 1] && str[i + 1] == '?')
	{
		exit_code = ft_itoa(g_exit_status);
		out = ft_strdup(exit_code);
		free(exit_code);
	}
	else if (str[i] == '$' && str[i + 1] == '\0')
		out = ft_strdup("$");
	else
	{
		key = ft_strjoin(str + 1, "=");
		if (!key)
			err_msg("Malloc\n");
		out = search_value(key, env);
		free(key);
	}
	return (out);
}
