#include "lexer.h"

int	get_type(char c)
{
	if (c == ' ')
		return (BLANK);
	else if (c == '\'')
		return (S_QUOTE);
	else if (c == '\"')
		return (D_QUOTE);
	else if (c == '|')
		return (PIPE);
	else if (c == ';')
		return (SEMI_COL);
	else if (c == '>')
		return (GREATER);
	else if (c == '<')
		return (LESSER);
	else if (c == '&')
		return (AMPERSAND);
	else if (c == '\\')
		return (ESCAPE);
	else if (c == '\t')
		return (TAB);
	else if (c == '\n')
		return (NEWLINE);
	else if (c == 0)
		return (CHAR_NULL);
	else
		return (DEFAULT);
}
void	quotes_content(char *src, char *dst)
{
	int		len;
	int		quote;
	int		i;
	int		j;
	char	c;

	len = ft_strlen(src);
	if (len <= 1)
		ft_strlcpy(dst, src, 1);
	quote = 0;
	i = 0;
	j = 0;
	while (i < len)
	{
		c = src[i];
		if ((c == '\'' || c == '\"') && quote == 0)
			quote = c;
		else if (c == quote)
			quote = 0;
		else
		{
			dst[j] = c;
			j++;
		}
		i++;
	}
	dst[j] = '\0';
}

int	generate_lexer(char *input, int size, t_lexer *lexer)
{
	t_token	*token;
	int		i;
	int		j;
	int		tmp;
	char	c;
	int		type;
	int		state;

	if (lexer == NULL)
		return (-1);
	if (size == 0)
	{
		lexer->token_num = 0;
		return (0);
	}
	lexer->token_list = malloc(sizeof(t_token));
	token = lexer->token_list;
	new_node(0, size);
	i = 0;
	j = 0;
	tmp = 0;
	c = input[i];
	while (c != '\0')
	{
		c = input[i];
		type = get_type(c);
		state = STATE_GENERAL;
		if (state = STATE_GENERAL)
		{
			if (type == S_QUOTE)
			{
				state = STATE_SQUOTE;
				token->arr[j++] = S_QUOTE;
				token->data = TOKEN;
			}
			else if (type == D_QUOTE)
			{
				state = STATE_DQUOTE;
				token->arr[j++] = D_QUOTE;
				token->data = TOKEN;
			}
			else if (type == ESCAPE)
			{
				token->arr[j++] = input[++i];
				token->data = TOKEN;
			}
			else if (type == DEFAULT)
			{
				token->arr[j++] = c;
				token->data = TOKEN;
			}
			else if (type == BLANK)
			{
				if (j > 0)
				{
					token->arr[j] = 0;
					token->next = malloc(sizeof(t_token));
					token = token->next;
					new_node(token, size - i);
					j = 0;
				}
			}
			else if ((type == PIPE) ||(type == SEMI_COL) || (type == GREATER) || (type == LESSER) || (type == AMPERSAND))
			{
				if (j > 0)
				{
					token->arr[j] = 0;
					token->next = malloc(sizeof(t_token));
					token = token->next;
					new_node(token, size - i);
					j = 0;
				}
			}
			token->arr[0] = type;
			token->arr[1] = 0;
			token->data = type;
			token->next = malloc(sizeof(t_token));
			token = token->next;
			new_node(token, size - i);
		}
		else if (state == STATE_SQUOTE)
		{
			token->arr[j++] = c;
			if (type == S_QUOTE)
				state = STATE_GENERAL;
		}
		else if (state == STATE_DQUOTE)
		{
			token->arr[j++] = c;
			if (type == D_QUOTE)
				state = STATE_GENERAL;
		}
		if (type == CHAR_NULL)
		{
			if (j > 0)
			{
				token->arr[j] = 0;
				tmp++;
				j = 0;
			}
		}
	}
	/**********************/
	int	k = 0;
	token = lexer->token_list;
	while (token != NULL)
	{
		if (token->data == TOKEN)
		{
			glob_t buf;
			glob(token->arr, GLOB_TILDE, NULL, &buf)
		}
	}
}