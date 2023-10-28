/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar_sign.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: eunbi <eunbi@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 19:06:41 by eunbi         #+#    #+#                 */
/*   Updated: 2023/10/28 20:05:55 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_len_dollar(char *str, int i)
{
	if (str[i] == '$' && (str[i + 1] == '\"' || str[i + 1] == '\''))
		return (1);
	while (str[i] && (str[i] == '$' || str[i] == '\"' || str[i] == '\''))
		i++;
	while (str[i] && str[i] != '$' && is_whitespace(str[i]) == false && str[i] != '+' \
		&& is_token(str[i]) == -1 && str[i] != '\"' && str[i] != '\'')
	{
		if (str[i] == '?')
			return (i);
		++i;
	}
	return (i - 1);
}

char	*combine_result(char *str, char *result, int i, int start)
{
	char	*new_result;
	char	*tmp;

	tmp = NULL;
	new_result = NULL;
	if (result == NULL)
		result = ft_substr(str, start, i - start);
	else
	{
		tmp = ft_substr(str, start, i - start);
		new_result = ft_strjoin(result, tmp);
		free(result);
		result = ft_strdup(new_result);
		free(new_result);
		free(tmp);
	}
	return (result);
}

char	*remove_quotes(char *str)
{
	int		i;
	int		start;
	char	*result;
	char	quote;

	i = 0;
	start = 0;
	result = NULL;
	quote = '\0';
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			quote = str[i];
		while (str[i] && str[i] == quote)
			i++;
		start = i;
		while (str[i] && str[i] != quote)
			i++;
		if (i > start)
			result = combine_result(str, result, i, start);
	}
	return (result);
}

// Replace the value between the indexes with its ENV value.
char *replace_between(t_parser *parser, char *data, int begin, int end)
{
	char 	*search;
	char	*begin_str;
	char	*end_str;
	char	*tmp;
	char	*result;

	if (begin < 0)
		return data;
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
char *replacer(char *str, t_parser *parser)
{
	char		quote;
	int			i;
	int 		next;

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
					return replace_between(parser, str, i, get_len_dollar(str, i));
				i++;
			}
		}
		else if (str[i] == '$')
			return replace_between(parser, str, i, get_len_dollar(str, i));
		i++;
	}
	return (str);
}

// Loop over the data until all values with a dollar sign are replaced.
// Before returning, remove all quotes from the string.
char *resolver(char *data, t_parser *parser)
{
	char		*result;
	char 		*str;
	char 		*tmp;

	str = data;
	tmp = str;
	result = NULL;
	while (ft_strcmp(str, result) != 0)
	{
		// free(str);
		str = tmp;

		result = replacer(str, parser);
		tmp = result;
	}
	// str = NULL;
	// if (str != NULL)
	// 	free(str);
	// free(tmp);
	return (remove_quotes(result));
}

// Loop over all arguments to check for dollar signs to replace.
void	determine_expanding(t_lexer *lexer, t_parser *parser)
{
	t_tokens	*head;
	char 		*tmp;

	tmp = NULL;
	head = lexer->token_list;
	while (lexer->token_list)
	{
		if (lexer->token_list->token == DEFAULT)
		{
			tmp = resolver(lexer->token_list->data, parser);
			// free(lexer->token_list->data); // TODO maybe can be removed
			if (tmp != NULL)
				lexer->token_list->data = tmp;
			else
				lexer->token_list->data = NULL;
		}
		lexer->token_list = lexer->token_list->next;
	}
	lexer->token_list = head;
}