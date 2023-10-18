/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 16:12:20 by eucho         #+#    #+#                 */
/*   Updated: 2023/10/19 00:19:59 by eunbi         ########   odam.nl         */
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
static char	*extract_word(char	*str, int i, int j, char quote)
{
	char	*tmp;

	tmp = NULL;
	if (str[i + 1] == quote)
		tmp = ft_strdup("''");
	else
		tmp = ft_substr(str, i + 1, j -1);
	return (tmp);
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
static int	arg_divider(t_lexer *lexer, char *str, int i, char quote)
{
	int		j;
	char	*tmp;

	j = 0;
	tmp = NULL;
	while (str[i + j] && (is_token(str[i + j]) == -1))
	{
		if (str[i + j] == '\'' || str[i + j] == '\"')
		{
			if (tmp != NULL)
				break ;
			quote = str[i + j];
			j += next_quote(str, i + j, quote);
			tmp = extract_word(str, i, j, quote);
		}
		else if (is_whitespace(str[i + j]) || quote != '\0')
			break ;
		else if (is_token(str[i + j++]) == -1)
		{
			free_tmp(tmp);
			tmp = ft_substr(str, i, j);
		}
	}
	find_dollar(tmp, lexer, quote);
	return (j);
}

bool	lexical_analyzer(t_lexer *lexer)
{
	int		i;
	int		j;
	char	quote;

	quote = '\0';
	i = 0;
	while (lexer->arg[i])
	{
		j = 0;
		i = skip_whitespace(lexer->arg, i);
		if (is_token(lexer->arg[i]) >= 0)
			j = take_tokens(lexer, lexer->arg, i);
		else
			j = arg_divider(lexer, lexer->arg, i, quote);
		if (j < 0)
			return (false);
		i = i + j;
	}
	free(lexer->arg);
	return (true);
}
