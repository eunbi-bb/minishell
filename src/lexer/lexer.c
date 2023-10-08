/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 16:12:20 by eucho         #+#    #+#                 */
/*   Updated: 2023/10/09 00:34:37 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

//Putting a token in a node
int	take_tokens(t_lexer_utils *lexer, char *str, int i)
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

int	quotes(char *str, int i)
{
	int	j;

	j = 1;
	while (str[i + j] && str[i + j] != str[i])
		j++;
	return (++j);
}

// char	*extract_token(char	*str, int i, int *j)
// {
// 	int		start;
// 	int		end;
// 	char	*token;

// 	start = i;
// 	end = i;
// 	while (str[end] && (is_token(str[end]) == -1))
// 	{
// 		if (str[end] == '\'' || str[end] == '\"')
// 			end += quotes(str, end);
// 		else if (is_whitespace(str[end]))
// 			break ;
// 		else
// 		{
// 			end++;
// 			if (is_token(str[end]) == -1)
// 				end++;
// 		}
// 	}
// 	token = ft_substr(str, start, end - start);
// 	*j = end - i;
// 	return (token);
// }

int	find_dollar(char *str)
{
	int		i;
	int 	start;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (str[i])
	{
		while (str[i] != '$' && str[i])
			i++;
		if (str[i] && str[i] == '$')
		{
			i = start;
			if (i > 0)
				tmp = ft_substr(str, 0, i);
			if (tmp != NULL)
				add_after(&lexer->token_list, new_token_node(tmp, DEFAULT))
		}
		while (str[i] && str[i] != '+' && str[i] != '$')
			i++;
		if (str[i] && str[i] == '+')
			add_after(&lexer->token_list, new_token_node("+", DEFAULT));
		if (i > start)
			tmp = ft_substr(str, start, i);
		if (tmp != NULL)
			add_after(&lexer->token_list, new_token_node(tmp, DOLLAR));
		i++;
	}
	return (i);
}

// Find a begining and end of a string
//(depending on white spaces or quotes)and generate a sub-string.
int	arg_divider(t_lexer_utils *lexer, char *str, int i)
{
	int j;
    char *tmp;
    char quote;

	j = 0;
	tmp = NULL:
	while (str[i + j] && (is_token(str[i + j]) == -1))
	{
		if (str[i + j] == '\'' || str[i + j] == '\"')
		{
			if (tmp != NULL)
				free(tmp);
			quote = str[i + j];
			j += quotes(str, i + j);
			tmp = ft_strtrim(ft_substr(str, i, j), &quote);
		}
		else if (is_whitespace(str[i + j]))
			break ;
		else
		{
			j++;
			if (is_token(str[i + j]) == -1)
			{
				if (tmp != NULL)
					free(tmp);
				tmp = ft_substr(str, i, j);
			}
		}
	}
	if (tmp != NULL)
	{
		if (quote == '\'')
			add_after(&lexer->token_list, new_token_node(tmp, S_QUOTE));
		else if (quote == '\"')
			add_after(&lexer->token_list, new_token_node(tmp, D_QUOTE));
		else
			add_after(&lexer->token_list, new_token_node(tmp, DEFAULT));
		free(tmp);
	}
	return (j);
}

bool	lexical_analyzer(t_lexer_utils *lexer)
{
	int	i;
	int	j;

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
