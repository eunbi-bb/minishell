#include "lexer.h"

int	skip_whitespace(char *str, int i)
{
	int		j;
	char	c;

	j = 0;
	while (str[i + j])
	{
		c = str[i + j];
		if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r')
			j++;
		i++;
	}
	return (j);
}

t_types	is_token(int c)
{
	t_lexer_utils type;
	int i;

	type.type_arr[PIPE] = '|';
	type.type_arr[LESSER] = '<';
	//type.type_arr[LESSER_TWO] = "<<";
	type.type_arr[GREATER] = '>';
	//type.type_arr[GREATER_TWO] = ">>";
	i = 0;
	while (i < 3)
	{
		if (type.type_arr[i] == c)
			return (i);
		i++;
	}
	return (0);
}

int	add_node(t_tokens **token_list, t_types type, char *str)
{
	t_tokens	*node;

	node = new_node(str, ft_strlen(str));
	add_after(NULL, node);
	return (1);
}

int	handle_token(t_tokens **token_list, char *str, int i)
{
	t_types	token;

	token = is_token(str[i]);
	if (token == NULL)
		return (0);
	if (token == GREATER && is_token(str[i + 1]) == GREATER)
	{
		if (!add_node(token_list, GREATER_TWO, NULL))
			return (-1);
		return (2);
	}
	else if (token == LESSER && is_token(str[i + 1] == LESSER))
	{
		if (!add_node(token_list, LESSER_TWO, NULL))
			return (-1);
		return (2);
	}
	else
	{
		if (!add_node(token_list, token, NULL))
			return (-1);
		return (1);
	}
	return (0);
}

int	s_quotes(char *str, int i)
{
	int	j;

	j = 0;
	if (str[i + j] == '\'')
	{
		j++;
		while (str[i + j] && str[i + j] != '\'')
			j++;
		j++;
	}
	return (j);
}

int	d_quotes(char *str, int i)
{
	int	j;

	j = 0;
	if (str[i + j] == '\"')
	{
		j++;
		while (str[i + j] && str[i + j] != '\"')
			j++;
		j++;
	}
	return (j);
}

int	in_quotes(t_tokens **token_list, char *str, int i)
{
	int	j;

	j = 0;
	while (str[i + j] && !(is_token(str[i + j])))
	{
		j += s_quotes(str, i + j);
		j += d_quotes(str, i + j);
		if (str[i + j] == ' ' || (str[i + j] >= '\t' && str[i + j] <= '\r'))
			break ;
		else
			j++;
	}
	if (!add_node(token_list, 0, ft_substr(str, i, j)))
		return (-1);
	return (j);
}

t_boolean	lexical_analyzer(t_lexer_utils *lexer)
{
	int	i;
	int	j;

	i = 0;
	while (lexer->arg[i])
	{
		j = 0;
		i += skip_whitespace(lexer->arg, i);
		if (is_token(lexer->arg[i]))
			j = handle_token(&lexer->token_list, &lexer->arg[i], i);
		else
			j = in_quotes(&lexer->token_list, &lexer->arg[i], i);
		if (j < 0)
			return (FALSE);
		i = i + j;
	}
	return (TRUE);
}

int	main(int argc, char **argv)
{
	t_lexer_utils	lexer;
	int				i;

	argv[0] = "hello";
	lexer.arg = argv[0];
	if (lexical_analyzer(&lexer) == TRUE)
	{
		i = 0;
		while (lexer.arg[i])
		{
			printf("tokens: %c\n", lexer.arg[i]);
			i++;
		}
	}
	return (0);
}