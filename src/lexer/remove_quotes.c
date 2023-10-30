/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   remove_quotes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: eunbi <eunbi@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 19:06:41 by eunbi         #+#    #+#                 */
/*   Updated: 2023/10/30 21:01:29 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*combine_result(char *str, char *result, int i, int start)
{
	char	*new_result;
	char	*tmp;

	tmp = NULL;
	new_result = NULL;
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
	return (result);
}

static char	*extract_word(char *str, int i, int start, char *result)
{
	char	quote;

	while (str[i])
	{
		if (str[i] == '\'')
		{
			quote = str[i];
			start = i;
			while (str[i] && (str[i] != quote))
				i++;
		}
		else if (str[i] == '\"')
		{
			quote = str[i];
			start = i;
			while (str[i] && (str[i] != quote))
				i++;
		}
		else
		{
			start = i;
			while (str[i] && (str[i] != '\"' && str[i] != '\''))
				i++;
		}
		if (i > start)
			result = combine_result(str, result, i, start);
		i++;
	}
	return (result);
}

char	*remove_quotes(char *str)
{
	int		i;
	int		start;
	char	*result;

	i = 0;
	start = 0;
	result = NULL;
	return (extract_word(str, i, start, result));
}

