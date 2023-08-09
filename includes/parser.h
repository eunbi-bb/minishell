#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include "../libft/libft.h"
# include "lexer.h"

typedef struct s_redir
{
	char		*file_name;
	t_types		redir_type;
	struct s_redir *next;
}	t_redir;

typedef struct	s_cmd
{
	/*First pointer will be the name of command*/
	char			**data;
	t_redir			*redir;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_parser_utils
{
	t_cmd	*cmd_list;
	char	*args;
	char	**env;
	int		pipes;
	int		pid;
	bool	reset;
	char	*command;
}	t_parser_utils;

void	parser(t_lexer_utils *lexer, t_parser_utils *parser);
#endif