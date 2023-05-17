#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include "../libft/libft.h"

typedef enum types
{
	TOKEN = -1,
	CHAR_NULL,
	BLANK,
	S_QUOTE,
	D_QUOTE,
	PIPE,
	SEMI_COL,
	GREATER,
	LESSER,
	AMPERSAND,
	ESCAPE,
	TAB,
	NEWLINE,
	DEFAULT,
} t_types;

typedef enum quotes
{
	STATE_SQUOTE,
	STATE_DQUOTE,
	STATE_GENERAL,
} t_quotes;

typedef	struct	s_token
{
	char			*arr;
	int				data;
	struct s_token	*prev;
	struct s_token	*next;
	char			*state;
}	t_token;

typedef struct s_lexer
{
	struct s_token	*token_list;
	int				token_num;
}	t_lexer;

t_token	*new_node(int data, int size);
void	add_before(t_token *current, t_token *new_node);
void	add_after(t_token *before, t_token *new_node);
void	del_node(t_token **head, t_token **tail, t_token *p);
#endif