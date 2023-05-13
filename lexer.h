#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include <glob.h>
# include "../libft/libft.h"

# define TOKEN -1

# define CHAR_NULL 0
# define BLANK 13
# define S_QUOTE 1
# define D_QUOTE 2
# define PIPE 3
# define SEMI_COL 4
# define GREATER 5
# define LESSER 6
# define AMPERSAND 7
# define ESCAPE 8
# define TAB 9
# define NEWLINE 10
# define DEFAULT 12

# define STATE_SQUOTE 11
# define STATE_DQUOTE 22
# define STATE_GENERAL 33

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