/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ssemanco <ssemanco@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/18 19:33:20 by ssemanco      #+#    #+#                 */
/*   Updated: 2023/10/26 19:39:52 by eunbi         ########   odam.nl         */
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

char	*expand(char *str, t_env *env)
{
	char	*key;
	int		i;
	char	*out;

	out = NULL;
	i = 0;
	if (str[i + 1] && str[i + 1] == '?')
		out = ft_strdup(ft_itoa(g_exit_status));
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