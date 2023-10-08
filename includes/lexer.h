#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <readline/readline.h>

bool	is_whitespace(char c);
int		skip_whitespace(char *s, int i);
int		is_token(int c);
#endif