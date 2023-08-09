#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <readline/readline.h>
# include "../libft/libft.h"

typedef enum boolean
{
	FALSE = 0,
	TRUE
}	t_boolean;

typedef enum types
{
	DEFAULT = -1,
	PIPE,
	LESSER,
	GREATER,
	HERE_DOC,
	APPEND
}	t_types;

// typedef enum quotes
// {
// 	STATE_SQUOTE = 10,
// 	STATE_DQUOTE,
// 	STATE_GENERAL,
// }	t_quotes;

typedef	struct	s_tokens
{
	char			*data;
	t_types			token;
	struct s_tokens	*next;
}	t_tokens;

typedef	struct s_lexer_utils
{
	char			*arg;
	t_tokens		*token_list;
	char			*type_arr;
	unsigned int	pipe_num;
	bool			heredoc;
	int				heredoc_in;
	int				heredoc_out;
}	t_lexer_utils;

t_tokens	*new_node(char *data);
t_tokens	*new_token_node(t_types token);
void		add_after(t_tokens **before, t_tokens *new_node);
bool		match_quotes(char *str);
bool		lexical_analyzer(t_lexer_utils *lexer);
int			arg_divider(t_lexer_utils *lexer, char *str, int i);
int			quotes(char *str, int i);
int			take_tokens(t_lexer_utils *lexer, char *str, int i);
#endif