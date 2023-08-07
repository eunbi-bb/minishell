#ifndef ERROR_H
# define ERROR_H
//File errors
# define ERROR_INFILE "infile: No such file or directory"
# define ERROR_OUTFILE "outfile: Error"
# define ERROR_PIPE_IN "infile: pipe error"
# define ERROR_PIPE_OUT "outfile: pipe error"
# define ERROR_FORK "Filed to fork\n"
//Syntax error
# define ERROR_QUOTE "syntax error: unexpected EOF while looking for matching"

# define ERROR_LEXER "lexer error"
# define ERROR_MEM "memory error"

//child error
# define ERROR_CHILD "Child error"

//dup2 error
# define ERROR_DUP2_OUT "failed dup2 for output"
# define ERROR_DUP2_IN "failed dup2 for input"

# include <errno.h>

void	err_msg(char *str);
void	perror_exit(char *str);
#endif