#include "../includes/lexer.h"

int	skip_whitespace(char *s, int i)
{
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == '\v' || s[i] == '\f' || s[i] == '\r')
		i++;
	return (i);
}

//Checking if the character is a token or not.
int	is_token(int c)
{
	t_lexer_utils type;
	int i;

	type.type_arr = "|<>";
	i = 0;
	while (type.type_arr[i])
	{
		if (type.type_arr[i] == c)
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

//Putting a token in a node
int	take_tokens(t_lexer_utils *lexer, char *str, int i)
{
	if (is_token(str[i]) == GREATER && is_token(str[i + 1]) == GREATER)
	{
		printf("Two greater token\n");
		add_after(&lexer->token_list, new_token_node(GREATER_TWO));
		return (2);
	}
	else if (is_token(str[i]) == LESSER && is_token(str[i + 1] == LESSER))
	{
		printf("Two lesser token\n");
		add_after(&lexer->token_list, new_token_node(HERE_DOC));
		return (2);
	}
	else if (is_token(str[i]) == PIPE)
	{
		add_after(&lexer->token_list, new_token_node(PIPE));
		// printf("new %d\n", new->token);
		//printf("og %d\n", lexer->token_list->token);
		lexer->pipe_num++;
		return (1);
	}
	return (0);
}

int	quotes(char *str, int i)
{
	int	j;

	j = 1;
	while (str[i + j] && str[i + j] != str[i])
		j++;
	return (++j);
}

//Find a begining and end of a string(depending on white spaces or quotes) and generate a sub-string. And add to a node.
int	arg_divider(t_tokens *token_list, char *str, int i)
{
	int		j;
	char	*tmp;
	char	quote;

	j = 0;
	while (str[i + j] && (is_token(str[i + j]) == -1))
	{
		if (str[i + j] == '\'' || str[i + j] == '\"')
		{
			quote = str[i + j];
			j += quotes(str, i + j);
			tmp = ft_strtrim(ft_substr(str, i, j), &quote);
		}
		else if (str[i + j] == ' ' || str[i + j] == '\t' || str[i + j] == '\n' || str[i + j] == '\v' || str[i + j] == '\f' || str[i + j] == '\r')
			break ;
		else
		{
			j++;
			if (is_token(str[i + j]) == -1)
				tmp = ft_substr(str, i, j);
		}
	}
	printf("tmp = %s\n", tmp);
	add_after(&token_list, new_node(tmp));
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
		if (is_token(lexer->arg[i]) >= 0)
			j = take_tokens(lexer, lexer->arg, i);
		else
			j = arg_divider(lexer->token_list, lexer->arg, i);
		if (j < 0)
			return (FALSE);
		i = i + j;
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
	lexer.pipe_num = 0;
	lexical_analyzer(&lexer);
	printf("pipe_num : %i\n", lexer.pipe_num);

	t_tokens *top = NULL;
	t_tokens *current = top;
	while(current != NULL)
	{
		printf("current->token:%c",current->token);
		current = current->next;
	}
	printf("token: %s\n", lexer.token_list->data);
	return (0);
}