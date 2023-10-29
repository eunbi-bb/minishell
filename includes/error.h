/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/18 11:24:23 by eucho         #+#    #+#                 */
/*   Updated: 2023/10/29 16:43:17 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
# define ERROR_NEWLINE "minishell: syntax error near unexpected token `newline'"
# define ERROR_PIPE	"minishell: syntax error near unexpected token `|'"
# define ERROR_LEXER "lexer error"
# define ERROR_MEM "memory error"

//child error
# define ERROR_CHILD "Child error"

//dup2 error
# define ERROR_DUP2_OUT "failed dup2 for output"
# define ERROR_DUP2_IN "failed dup2 for input"

//Command error
# define ERROR_CMD "command not found"
# define EXIT_CMD 127
# define ERROR_EXECVE "execve error"
# define ERROR_DIR  " Is a directory"
# define EXIT_DIR 126
# define ERROR_PERMISSION "Permission denied"

//Signal error
# define ERROR_SIG "signal error" 

//fds error
# define ERROR_FDS "fds malloc error"

# include <errno.h>
# include <unistd.h>
# include <stdbool.h>

bool	input_check(char *str);
int		err_msg(char *str);
void	perror_exit(char *str);
int		cmd_error(char *cmd, char *error, int exit_code);
#endif