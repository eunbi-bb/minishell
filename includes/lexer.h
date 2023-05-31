#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include "../libft/libft.h"

typedef enum boolean
{
	FALSE = 0,
	TRUE
}	t_boolean;

typedef enum types
{
	PIPE,
	LESSER,
	GREATER,
	HERE_DOC,
	GREATER_TWO,
}	t_types;

typedef enum quotes
{
	STATE_SQUOTE = 10,
	STATE_DQUOTE,
	STATE_GENERAL,
}	t_quotes;

typedef	struct	s_tokens
{
	char			*data;
	t_types			token;
	int				*arr;
	struct s_tokens	*prev;
	struct s_tokens	*next;
}	t_tokens;

typedef	struct s_lexer_utils
{
	char		*arg;
	t_tokens	*token_list;
	char		*type_arr;
}	t_lexer_utils;

t_tokens	*new_node(char *data);
t_tokens	*new_token_node(char token);
void	add_before(t_tokens *current, t_tokens *new_node);
void	add_after(t_tokens *before, t_tokens *new_node);
void	del_node(t_tokens **head, t_tokens **tail, t_tokens *p);
#endif