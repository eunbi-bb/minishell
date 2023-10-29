/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar_sign.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: eunbi <eunbi@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 19:06:41 by eunbi         #+#    #+#                 */
/*   Updated: 2023/10/29 14:05:48 by eunbi         ########   odam.nl         */
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

char	*extract_word(char *str, int i, int start, char *result)
{
	char	quote;

	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i++];
			start = i;
			while (str[i] && (str[i] != quote))
				i++;
		}
		else
		{
			start = i;
			while (str[i] && (str[i] != '\"' && str[i] != '\''))
				i++;
		}
		if (i > start)
			result = combine_result(str, result, i, start);
	}
	return (result);
}

char	*remove_quotes(char *str)
{
	int		i;
	int		start;
	char	*result;

	i = 0;
	start = 0;
	result = NULL;
	return(extract_word(str, i, start, result));
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
		return ft_strdup(data);
	if (end < 0)
		end = ft_strlen(data);
	tmp = ft_substr(data, begin, end - begin + 1);
	search = expand(tmp, parser->env);
	free(tmp);
	begin_str = ft_substr(data, 0, begin);
	end_str = ft_substr(data, end + 1, ft_strlen(data));
	tmp = ft_strjoin(begin_str, search);
	free(begin_str);
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
	return ft_strdup(str);
}

int count_dollar(char *str)
{
	int			i;
	int			count;

	i = 0;
	count = 0;
	while (str[i])
	{// TODO check if there is a value (no ' " or space") after the dollar
		if (str[i] == '$')
			count++;
		i++;
	}
	return count;
}

// Loop over the data until all values with a dollar sign are replaced.
// Before returning, remove all quotes from the string.
char *resolver(char *data, t_parser *parser)
{
	char	*result = NULL;

	int replace_count = count_dollar(data);
	if (replace_count == 0)
		return remove_quotes(data);
	int replaced_count = 0;
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
		{
			free(result);
		}
	return (data);
}

// Loop over all arguments to check for dollar signs to replace.
void	determine_expanding(t_lexer *lexer, t_parser *parser)
{
	char	*tmp;
	t_tokens	*curr;

	curr = lexer->token_list;
	while (curr)
	{
		if (curr->token == DEFAULT)
		{
			tmp = resolver(curr->data, parser);
			free(curr->data);
			curr->data = tmp;
		}
		curr = curr->next;
	}
}