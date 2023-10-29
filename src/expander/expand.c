/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ssemanco <ssemanco@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/18 19:33:20 by ssemanco      #+#    #+#                 */
/*   Updated: 2023/10/29 14:54:33 by eucho         ########   odam.nl         */
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

static int	count_dollar(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$')
			count++;
		i++;
	}
	return (count);
}

// Loop over the data until all values with a dollar sign are replaced.
// Before returning, remove all quotes from the string.
static char	*expanded_data(char *data, t_parser *parser)
{
	char	*result;
	int		replace_count;
	int		replaced_count;

	result = NULL;
	replace_count = count_dollar(data);
	if (replace_count == 0)
		return (remove_quotes(data));
	replaced_count = 0;
	while (replaced_count < replace_count)
	{
		if (result != NULL)
		{
			data = strdup(result);
			free(result);
		}
		result = replacer(data, parser);
		if (replaced_count > 0)
			free(data);
		replaced_count++;
	}
	data = remove_quotes(result);
	if (result != NULL)
		free(result);
	return (data);
}

// Loop over all arguments to check for dollar signs to replace.
void	expand_token_list(t_lexer *lexer, t_parser *parser)
{
	char		*tmp;
	t_tokens	*curr;

	curr = lexer->token_list;
	while (curr)
	{
		if (curr->token == DEFAULT)
		{
			tmp = expanded_data(curr->data, parser);
			free(curr->data);
			curr->data = tmp;
		}
		curr = curr->next;
	}
}
