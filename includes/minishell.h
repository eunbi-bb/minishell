#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "lexer.h"
# include "parser.h"

int		here_document(t_cmd	*cmd, t_lexer_utils *lexer);
int		create_heredoc(char *delim, char *filename);
char	*tmp_filename(int i);

typedef struct	s_global
{
	int		exit_stat;
	int		signal;

}				t_global;

t_global	g_global;

#endif