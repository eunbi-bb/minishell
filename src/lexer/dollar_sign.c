/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar_sign.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: eunbi <eunbi@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 19:06:41 by eunbi         #+#    #+#                 */
/*   Updated: 2023/10/27 22:31:59 by eunbi         ########   odam.nl         */
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
		++i;
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

	i = 0;
	start = 0;
	result = NULL;
	while (str[i])
	{
		while (str[i] && (str[i] == '\'' || str[i] == '\"'))
			i++;
		start = i;
		while (str[i] && str[i] != '\'' && str[i] != '\"')
			i++;
		if (i > start)
			result = combine_result(str, result, i, start);
	}
	return (result);
}

char *replacer(char *data, t_parser *parser)
{
	char		quote;
	char		*expand_value;
	int			i;
	int			begin_expand = -1;
	int			end_expand = -1;
	int 		next;

	i = 0;
	quote = '\0';
	while (data[i] && end_expand < 0)
	{
		if (data[i] == '\'' || data[i] == '\"')
		{
			quote = data[i];
			next = i + next_quote(data, i);
			while (i < next && end_expand < 0)
			{
				if (data[i] == '$' && quote == '\"')
				{
					begin_expand = i;
					end_expand = get_len_dollar(data, begin_expand);
				}
				else
					i++;
			}
		}
		else if (data[i] == '$')
		{
			begin_expand = i;
			end_expand = get_len_dollar(data, begin_expand);
			i += end_expand;
		}
		i++;
	}
	if (begin_expand < 0)
		return data;
	if (end_expand < 0)
		end_expand = ft_strlen(data);
	char *found_value = NULL;
	found_value = ft_substr(data, begin_expand, end_expand - begin_expand + 1);
	char *search = expand(found_value, parser->env);
	expand_value = ft_strdup(search);
	free(search);
	free(found_value);
	char	*begin = ft_substr(data, 0, begin_expand);
	char	*end = ft_substr(data, end_expand + 1, ft_strlen(data));
	char	*tmp = ft_strjoin(begin, expand_value);
	char	*result = ft_strjoin(tmp, end);
	free(expand_value);
	free(tmp);
	free(begin);
	free(end);
	return (result);
}

void	determine_expanding(t_lexer *lexer, t_parser *parser)
{
	t_tokens	*head;
	char		*result;
	char 		*data;
	char 		*tmp;

	head = lexer->token_list;
	result = ft_strdup("");
	tmp = NULL;
	data = NULL;
	while (lexer->token_list)
	{
		if (lexer->token_list->token == DEFAULT)
		{
			if (tmp != NULL)
				free(tmp);
			data = ft_strdup(lexer->token_list->data);
			tmp = ft_strdup(data);
			while (ft_strcmp(data, result) != 0)
			{
				free(data);
				data = ft_strdup(tmp);
				free(result);
				result = replacer(data, parser);
				free(tmp);
				tmp = ft_strdup(result);
			}
			free(lexer->token_list->data);
			char *result2 = remove_quotes(result);
			if (result2 != NULL)
				lexer->token_list->data = ft_strdup(result2);
			else
				lexer->token_list->data = NULL;
			free(result2);
			lexer->token_list = lexer->token_list->next;
		}
		else
			lexer->token_list = lexer->token_list->next;
	}
	if (data)
		free(data);
	free(tmp);
	lexer->token_list = head;
}
