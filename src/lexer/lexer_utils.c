/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 19:57:13 by eucho         #+#    #+#                 */
/*   Updated: 2023/10/15 14:35:54 by eucho         ########   odam.nl         */
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

//Checking if the character is a token or not.
int	is_token(int c)
{
	t_lexer_utils	lexer;
	int				i;

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
			{
				num_s++;
				i++;
			}
			else if (quote == '\"')
			{
				num_d++;
				i++;
			}
			while (str[i] != quote && str[i])
				i++;
		}
		else
			i++;
	}
	if ((num_s % 2) != 0 || (num_d % 2) != 0)
		return (false);
	return (true);
}