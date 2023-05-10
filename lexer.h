#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>

# define BLANK 0
# define S_QUOTE 1
# define D_QUOTE 2
# define PIPE 3
# define SEMI_COL 4
# define GREATER 5
# define LESSER 6
# define AMPERSAND 7
# define ESCAPE 8
# define DEFAULT 9

typedef	struct	s_token
{
	char	*str;
	int		data;
	struct s_token *prev;
	struct s_token *next;
}				t_token;
#endif