/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/29 14:45:17 by eucho         #+#    #+#                 */
/*   Updated: 2023/10/29 16:42:40 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	dollar_len(char *str, int i)
{
	if (str[i] == '$' && (str[i + 1] == '\"' || str[i + 1] == '\''))
		return (1);
	while (str[i] && (str[i] == '$' || str[i] == '\"' || str[i] == '\''))
		i++;
	while (str[i] && str[i] != '$' && str[i] != '\"' && str[i] != '\'' \
		&& str[i] != '+' && is_token(str[i]) == -1 \
		&& is_whitespace(str[i]) == false)
	{
		if (str[i] == '?')
			return (i);
		++i;
	}
	return (i - 1);
}

// Replace the value between the indexes with its ENV value.
char	*expand_data(t_parser *parser, char *data, int begin, int end)
{
	char	*search;
	char	*begin_str;
	char	*end_str;
	char	*tmp;
	char	*result;

	if (begin < 0)
		return (ft_strdup(data));
	if (end < 0)
		end = ft_strlen(data);
	tmp = ft_substr(data, begin, end - begin + 1);
	search = expand(tmp, parser->env);
	free(tmp);
	begin_str = ft_substr(data, 0, begin);
	end_str = ft_substr(data, end + 1, ft_strlen(data));
	tmp = ft_strjoin(begin_str, search);
	free(begin_str);
	free(search);
	result = ft_strjoin(tmp, end_str);
	free(tmp);
	free(end_str);
	return (result);
}

// Find the dollar sign value, and replace it with the ENV value.
char	*replacer(char *str, t_parser *parser)
{
	char	quote;
	int		i;
	int		next;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			next = i + next_quote(str, i);
			while (i < next)
			{
				if (str[i] == '$' && quote == '\"')
					return (expand_data(parser, str, i, dollar_len(str, i)));
				i++;
			}
		}
		else if (str[i] == '$')
			return (expand_data(parser, str, i, dollar_len(str, i)));
		i++;
	}
	return (ft_strdup(str));
}
