/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 16:12:20 by eucho         #+#    #+#                 */
/*   Updated: 2023/10/27 21:59:35 by eunbi         ########   odam.nl         */
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

static char	*combine_args(char *str, char *tmp, int i, int j)
{
	char	*sub_str;
	char	*tmp2;

	sub_str = NULL;
	tmp2 = NULL;
	if (tmp == NULL)
		tmp = ft_substr(str, i, j);
	else
	{
		sub_str = ft_substr(str, i + ft_strlen(tmp) , j - ft_strlen(tmp));
		tmp2 = ft_strjoin(tmp, sub_str);
		free(tmp);
		free(sub_str);
		tmp = ft_strdup(tmp2);
		free(tmp2);
	}
	return (tmp);
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

	j = 0;
	tmp = NULL;
	while (str[i + j] && (is_token(str[i + j]) == -1))
	{
		if (str[i + j] == '\'' || str[i + j] == '\"')
			j += next_quote(str, i + j) + 1;
		else if (is_whitespace(str[i + j]))
			break ;
		else if (is_token(str[i + j]) == -1)
		{
			while (str[i + j] && is_token(str[i + j]) == -1 && !is_whitespace(str[i + j]) \
				&& str[i + j] != '\'' && str[i + j] != '\"')
				j++;
		}
		tmp = combine_args(str, tmp, i, j);
	}
	add_after(&lexer->token_list, new_token_node(tmp, DEFAULT));
	free_tmp(tmp);
	return (j);
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
