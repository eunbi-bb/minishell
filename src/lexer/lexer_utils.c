/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 19:57:13 by eucho         #+#    #+#                 */
/*   Updated: 2023/10/02 19:59:24 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' \
		|| c == '\v' || c == '\f' || c == '\r');
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
