/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 16:12:20 by eucho         #+#    #+#                 */
/*   Updated: 2023/10/26 20:06:50 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		add_after(&lexer->token_list, new_token_node(NULL, APPEND, '\0'));
		return (2);
	}
	else if (is_token(str[i]) == LESSER && is_token(str[i + 1]) == LESSER)
	{
		add_after(&lexer->token_list, new_token_node(NULL, HERE_DOC, '\0'));
		lexer->heredoc = true;
		return (2);
	}
	else if (is_token(str[i]) == GREATER)
		add_after(&lexer->token_list, new_token_node(NULL, GREATER, '\0'));
	else if (is_token(str[i]) == LESSER)
		add_after(&lexer->token_list, new_token_node(NULL, LESSER, '\0'));
	else if (is_token(str[i]) == PIPE)
	{
		add_after(&lexer->token_list, new_token_node(NULL, PIPE, '\0'));
		lexer->pipe_num++;
	}
	else
		return (0);
	return (1);
}

/*
*	Extract the word between quotes.
*	If there is nothing between the quotes, set tmp to an empty string.
*/
// static char	*extract_word(char	*str, int i, int j, char quote)
// {
// 	char	*tmp;

// 	tmp = NULL;
// 	if (str[i + 1] == quote)
// 		tmp = ft_strdup("");
// 	else if (quote != '\0')
// 		tmp = ft_substr(str, i + 1, j - 2);
// 	else
// 		tmp = ft_substr(str, i + 1, j - 1);
// 	return (tmp);
// }

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
			tmp2 = ft_strjoin(tmp, ft_substr(str, i + ft_strlen(tmp) , j - ft_strlen(tmp)));
			free(tmp);
			tmp = ft_strdup(tmp2);
			free(tmp2);
		}
	}
	add_after(&lexer->token_list, new_token_node(tmp, DEFAULT, '\0'));
	free_tmp(tmp);
	return (j);
}

static int	get_len_dollar(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '$' || is_whitespace(str[i]) \
			|| is_token(str[i]) >= 0 || str[i] == '\"' || str[i] == '\'')
		{
			--i;
			break ;
		}
		else if (str[i] == '+')
			break ;
		i++;
	}
	return (i);
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

	i = 0;
	while (data[i] && end_expand < 0)
	{
		if (data[i] == '\'' || data[i] == '\"')
		{
			quote = data[i];
			int next = i + next_quote(data, i, quote);
			while (i < next)
			{
				if (data[i] == '$' && quote == '\"')
				{
					begin_expand = i;
					end_expand = get_len_dollar(data, begin_expand + 1);
					i += end_expand;
				}
				else
					i++;
			}
		}
		else if (data[i] == '$')
		{
			begin_expand = i;
			end_expand = get_len_dollar(data, begin_expand + 1);
			i += end_expand;
		}
		i++;
	}
	if (begin_expand < 0)
		return data;
	if (end_expand < 0)
		end_expand = ft_strlen(data);
	char *found_value = ft_substr(data, begin_expand, end_expand);
	expand_value = ft_strdup(expand(found_value, parser->env));
	// printf("Found value %s\n", found_value);
	free(found_value);

	// printf("Replacing with value %s\n", expand_value);

	char *begin = ft_substr(data, 0, begin_expand);
	char *end = ft_substr(data, end_expand + 1, ft_strlen(data));
	// printf("Begin %s\n", begin);
	// printf("end %s\n", end);
	char *result = ft_strjoin(ft_strjoin(begin, expand_value), end);
	free(begin);
	free(end);
	// printf("Result %s\n", result);

	return result;
}


void	determine_expanding(t_lexer *lexer, t_parser *parser)
{
	// printf("TEST\n");
	t_tokens	*head;

	head = lexer->token_list;

	while (lexer->token_list)
	{
		char *result = "";
		char *data;
		char *tmp;
		data = ft_strdup(lexer->token_list->data);

		tmp = ft_strdup(data);
		while (ft_strcmp(data, result) != 0)
		{
			data = ft_strdup(tmp);
			result = replacer(data, parser);
			tmp = ft_strdup(result);
		}
		free(lexer->token_list->data);
		lexer->token_list->data = ft_strdup(result);
		lexer->token_list = lexer->token_list->next;
	}

	lexer->token_list = head;
}



// static int	get_len_dollar(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '$' || str[i] == '+' 
// 			|| is_whitespace(str[i]) || is_token(str[i]) >= 0)
// 			break ;
// 		i++;
// 	}
// 	return (i);
// }

// char	*expand_dollar(t_tokens *token, int i)
// {
// 	int	len;

// 	if (token->data[i + 1] && token->data[i + 1] == '?')
// 		expand_exitcode();
// 	else
// 	{
// 		len = get_len_dollar(&token->data[i + 1]);
// 		expand_var(token, i, len);
// 	}
// }

// void	determine_expanding(t_lexer *lexer)
// {
// 	t_tokens	*head;
// 	char		quote;
// 	char		*tmp;
// 	int			i;

// 	i = 0;
// 	head = lexer->token_list;
// 	while (lexer->token_list->data[i])
// 	{
// 		if (lexer->token_list->data[i] == '\'' || lexer->token_list->data[i] == '\"')
// 		{
// 			quote = lexer->token_list->data[i];
// 			while (i < next_quote(lexer->token_list->data, i, quote))
// 			{
// 				if (lexer->token_list->data[i] == '$' && quote == '\"')
// 					tmp = expand_dollar(lexer->token_list, i);
// 				else
// 					i++;
// 			}
// 		}
// 		else if (lexer->token_list->data[i] == '$')
// 			tmp = expand_dollar(lexer->token_list, i);
// 		else
// 			i++;
// 	}
// 	lexer->token_list = head;
// }



// static int	arg_divider(t_lexer *lexer, char *str, int i, char quote)
// {
// 	int		j;
// 	char	*tmp;

// 	j = 0;
// 	tmp = NULL;
// 	while (str[i + j] && (is_token(str[i + j]) == -1))
// 	{
// 		if (str[i + j] == '\'' || str[i + j] == '\"')
// 		{
// 			if (tmp != NULL)
// 				break ;
// 			quote = str[i + j];
// 			j += next_quote(str, i + j, quote);
// 			tmp = extract_word(str, i, j, quote);
// 		}
// 		else if (is_whitespace(str[i + j]) || quote != '\0')
// 			break ;
// 		else if (is_token(str[i + j++]) == -1)
// 		{
// 			free_tmp(tmp);
// 			tmp = ft_substr(str, i, j);
// 		}
// 	}
// 	find_dollar(tmp, lexer, quote);
// 	return (j);
// }

