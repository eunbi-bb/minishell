#include "../includes/lexer.h"

int	skip_whitespace(char *s, int i)
{
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == '\v' || s[i] == '\f' || s[i] == '\r')
		i++;
	return (i);
}

//Checking if the character is a token or not.
t_types	is_token(int c)
{
	t_lexer_utils type;
	int i;

	type.type_arr = "|<>";
	i = 0;
	while (type.type_arr[i])
	{
		if (type.type_arr[i] == c)
			return (i);
		i++;
	}
	return (0);
}

//Putting a token in a node
int	take_tokens(t_tokens *token_list, char *str, int i)
{
	if (is_token(str[i]) == GREATER && is_token(str[i + 1]) == GREATER)
	{
		add_after(token_list, new_token_node(GREATER_TWO));
		return (2);
	}
	else if (is_token(str[i]) == LESSER && is_token(str[i + 1] == LESSER))
	{
		add_after(token_list, new_token_node(HERE_DOC));
		return (2);
	}
	else if (is_token(str[i]) == PIPE)
	{
		add_after(token_list, new_token_node(str[i]));
		//pipe_num++;
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
	if (str[i + j] != '\"')
	{
		j++;
		while (str[i + j] && str[i + j] != '\"')
			j++;
		j++;
	}
	return (j);
}

//Find a begining and end of a string(depending on white spaces or quotes) and generate a sub-string. And add to a node.
int	in_quotes(t_tokens *token_list, char *str, int i)
{
	int		j;
	char	*tmp;

	j = 0;
	while (str[i + j] && !(is_token(str[i + j])))
	{
		if (str[i + j] == '\'')
		{
			j += s_quotes(str, i + j);
			tmp = ft_strtrim(ft_substr(str, i, j), "\'");
		}
		else if (str[i + j] == '\"')
		{
			j += d_quotes(str, i + j);
			tmp = ft_strtrim(ft_substr(str, i, j), "\"");
		}
		else if (str[i + j] == ' ' || str[i + j] == '\t' || str[i + j] == '\n' || str[i + j] == '\v' || str[i + j] == '\f' || str[i + j] == '\r')
			break ;
		else
		{
			j++;
			tmp = ft_substr(str, i, j);
		}
	}
	//printf("tmp = %s\n", tmp);
	add_after(token_list, new_node(tmp));
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
		i = skip_whitespace(lexer->arg, i);
		//printf("after skipwhite : %d\n", i);
		if (is_token(lexer->arg[i]))
			j = take_tokens(lexer->token_list, lexer->arg, i);
		else
			j = in_quotes(lexer->token_list, lexer->arg, i);
		if (j < 0)
			return (FALSE);
		i = i + j;
		//printf("i + j = %d\n", i);
	}
	return (TRUE);
}


//Checking if quotes are in a pair.
t_boolean	match_quotes(char *str)
{
	int	i;
	int	j;
	int	num_s;
	int	num_d;

	i = 0;
	num_s = 0;
	num_d = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			num_s++;
			j = i + 1;
			while (str[j] != '\'' && str[j])
			{
				if (str[j] == '\'')
					num_s++;
				j++;
			}
		}
		else if (str[i] == '\"')
		{
			num_d++;
			j = i + 1;
			while (str[j] != '\"' && str[j])
			{
				if (str[j] == '\"')
					num_d++;
				j++;
			}
		}
		i++;
	}
	if ((num_s % 2) != 0 || (num_d % 2) != 0)
		return (FALSE);
	return (TRUE);
}

int	main(void)
{
	t_lexer_utils lexer;
	char	*str;

	// str = "    grep 'Hello World'";
	str = "    grep 'Hello World' | cat -e    ";
	lexer.arg = ft_strtrim(str, " ");
	if (match_quotes(lexer.arg) == FALSE)
		return (-1);
	lexical_analyzer(&lexer);
	return (0);
}