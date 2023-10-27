/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 16:12:20 by eucho         #+#    #+#                 */
/*   Updated: 2023/10/27 21:02:21 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "error.h"

/*
*	Scan an input string and tokenizes specific characters such as,
*	>>	: APPEND
*	<<	: HERE_DOC
*	>	: GREATER
*	<	: LESSER
*	|	: PIPE
*	And store these tokens in a token_list. Return 1 or 2 if it is a token,
*	to skip in the entire string.
*/
static int	take_tokens(t_lexer *lexer, char *str, int i)
{
	if (is_token(str[i]) == GREATER && is_token(str[i + 1]) == GREATER)
	{
		add_after(&lexer->token_list, new_token_node(NULL, APPEND));
		return (2);
	}
	else if (is_token(str[i]) == LESSER && is_token(str[i + 1]) == LESSER)
	{
		add_after(&lexer->token_list, new_token_node(NULL, HERE_DOC));
		lexer->heredoc = true;
		return (2);
	}
	else if (is_token(str[i]) == GREATER)
		add_after(&lexer->token_list, new_token_node(NULL, GREATER));
	else if (is_token(str[i]) == LESSER)
		add_after(&lexer->token_list, new_token_node(NULL, LESSER));
	else if (is_token(str[i]) == PIPE)
	{
		add_after(&lexer->token_list, new_token_node(NULL, PIPE));
		lexer->pipe_num++;
	}
	else
		return (0);
	return (1);
}

void	free_tmp(char *tmp)
{
	if (tmp != NULL)
		free(tmp);
}
/*
*	Dividing given string based on quotes and white spaces.
*	After division, parse it to find_dollar() to find '$' for expansion
*	and generate nodes in the token_list.
*/
static int	arg_divider(t_lexer *lexer, char *str, int i)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	quote;

	j = 0;
	tmp = NULL;
	while (str[i + j] && (is_token(str[i + j]) == -1))
	{
		if (str[i + j] == '\'' || str[i + j] == '\"')
		{
			quote = str[i + j];
			j += next_quote(str, i + j, quote) + 1;
		}
		else if (is_whitespace(str[i + j]))
			break ;
		else if (is_token(str[i + j]) == -1)
		{
			while (str[i + j] && is_token(str[i + j]) == -1 && is_whitespace(str[i + j]) == false \
				&& str[i + j] != '\'' && str[i + j] != '\"')
				j++;
		}
		if (tmp == NULL)
			tmp = ft_substr(str, i, j);
		else
		{
			char	*sub_str = ft_substr(str, i + ft_strlen(tmp) , j - ft_strlen(tmp));
			tmp2 = ft_strjoin(tmp, sub_str);
			free(tmp);
			free(sub_str);
			tmp = ft_strdup(tmp2);
			free(tmp2);
		}
	}
	add_after(&lexer->token_list, new_token_node(tmp, DEFAULT));
	free_tmp(tmp);
	return (j);
}

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

bool	lexical_analyzer(t_lexer *lexer)
{
	int		i;
	int		j;

	i = 0;
	while (lexer->arg[i])
	{
		j = 0;
		i = skip_whitespace(lexer->arg, i);
		if (is_token(lexer->arg[i]) >= 0)
			j = take_tokens(lexer, lexer->arg, i);
		else
			j = arg_divider(lexer, lexer->arg, i);
		if (j < 0)
			return (false);
		i = i + j;
	}
	free(lexer->arg);
	return (true);
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
			next = i + next_quote(data, i, quote);
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

char	*ft_strncpy(char *dst, char *src, int n)
{
	int	i;

	i = 0;
	while (i < n && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*remove_quotes(char *str)
{
	int		i;
	int		start;
	char	*result;
	char	*new_result;
	char	*tmp;

	i = 0;
	start = 0;
	tmp = NULL;
	result = NULL;
	i = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == '\'' || str[i] == '\"'))
			i++;
		start = i;
		while (str[i] && str[i] != '\'' && str[i] != '\"')
			i++;
		if (i > start)
		{
			// tmp = ft_substr(str, start, i - start);
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
		}
	}
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
