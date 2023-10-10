/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar_sign.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: eunbi <eunbi@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 19:06:41 by eunbi         #+#    #+#                 */
/*   Updated: 2023/10/10 12:06:26 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_len_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' || str[i] == '+' \
			|| is_whitespace(str[i]) || is_token(str[i]) >= 0)
			break ;
		i++;
	}
	return (i);
}

int	get_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' || is_whitespace(str[i]))
			break ;
		i++;
	}
	return (i);
}

int	generate_node(char *str, int i, t_lexer_utils *lexer, char quote)
{
	char	*tmp;
	int		len;

	len = get_len(&str[i]);
	tmp = ft_substr(str, i, len);
	// printf("general : %s\n", tmp);
	add_after(&lexer->token_list, new_token_node(tmp, DEFAULT, quote));
	free(tmp);
	i += len;
	return (i);
}

int	split_dollar(char *str, int i, t_tokens *token_list, char quote)
{
	char	*tmp;
	int		len;

	if (str[i + 1] && str[i + 1] == '?')
	{
		tmp = ft_substr(str, i, 2);
		// printf("qusetion : %s\n", tmp);
		add_after(&token_list, new_token_node(tmp, QUESTION, quote));
		i += 2;
	}
	else if (str[i + 1] && str[i + 1] == '$')
	{
		tmp = ft_substr(str, i, 2);
		// printf("pid : %s\n", tmp);
		add_after(&token_list, new_token_node(tmp, PID, quote));
		i += 2;
	}
	else
	{
		len = get_len_dollar(&str[i + 1]) + 1;
		tmp = ft_substr(str, i, len);
		// printf("dollar : %s\n", tmp);
		add_after(&token_list, new_token_node(tmp, DOLLAR, quote));
		i += len;
	}
	free(tmp);
	return (i);
}


void	find_dollar(char *str, t_lexer_utils *lexer, char quote)
{
	char	*tmp;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i = split_dollar(str, i, lexer->token_list, quote);
		}
		else if (str[i] == '+')
		{
			tmp = ft_strdup("+");
			// printf("%s\n", tmp);
			add_after(&lexer->token_list, new_token_node(tmp, DEFAULT, quote));
			free(tmp);
			i++;
		}
		else if (str[i] != '+' && !is_whitespace(str[i]))
			i = generate_node(str, i, lexer, quote);
		else
			i++;
	}
}
