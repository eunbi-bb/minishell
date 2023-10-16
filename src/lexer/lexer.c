/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 16:12:20 by eucho         #+#    #+#                 */
/*   Updated: 2023/10/16 21:38:02 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

//Putting a token in a node
int	take_tokens(t_lexer_utils *lexer, char *str, int i)
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

int	quotes(char *str, int i, char quote)
{
	int	j;

	j = 0;
	if (str[i + j] == quote)
	{
		j++;
		while (str[i + j] && str[i + j] != quote)
			j++;
	}
	return (j);
}

void free_tmp(char *value)
{
	if (value != NULL)
		free(value);
}
// Find a begining and end of a string
//(depending on white spaces or quotes)and generate a sub-string.
int	arg_divider(t_lexer_utils *lexer, char *str, int i, char quote)
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
				break;
			quote = str[i + j];
			j += quotes(str, i + j, quote);
			// if (str[i + j] != quote)
				tmp = ft_substr(str, i + 1, j -1);
			// else
			// 	tmp = ft_strdup("''");
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
	free_tmp(tmp);
	return (j);
}

bool	lexical_analyzer(t_lexer_utils *lexer)
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
