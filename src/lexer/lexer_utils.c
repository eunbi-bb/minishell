/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 19:57:13 by eucho         #+#    #+#                 */
/*   Updated: 2023/10/18 16:21:25 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' \
		|| c == '\v' || c == '\f' || c == '\r')
		return (true);
	else
		return (false);
}

int	skip_whitespace(char *s, int i)
{
	while (is_whitespace(s[i]))
		i++;
	return (i);
}

// Checking if the character is a token or not.
int	is_token(int c)
{
	t_lexer	lexer;
	int		i;

	lexer.type_arr = "|<>";
	i = 0;
	while (lexer.type_arr[i])
	{
		if (lexer.type_arr[i] == c)
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

// Checking if quotes are in a pair.
bool	match_quotes(char *str)
{
	int		i;
	int		num_s;
	int		num_d;
	char	quote;

	i = 0;
	num_s = 0;
	num_d = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			if (quote == '\'')
				num_s++;
			else if (quote == '\"')
				num_d++;
			i++;
			while (str[i] != quote && str[i])
				i++;
		}
		else
			i++;
	}
	return ((num_s % 2 == 0) && (num_d % 2 == 0));
}

/*
*	Finding an end quote.
*	It returns the length from the beginning quote to the end quote. 
*/
int	next_quote(char *str, int i, char quote)
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