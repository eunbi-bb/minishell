#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include "../libft/libft.h"
# include "lexer.h"

typedef struct	s_cmd
{
	char			**data;
	char			*option;
	int				redirection;
	char			*file;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_parser_utils
{
	char	*args;
	char	**paths;
	char	**envp;
	char	*pwd;
	char	*prev_pwd;
	int		pipes;
	int		pid;
	t_boolean	heredoc;
	t_boolean	reset;
}	t_parser_utils;

typedef struct	s_redir_utils
{
	struct s_tokens			*redir;
	struct s_tokens			*lexer_lst;
	int						num_redir;
	struct s_parser_utils	*utils;
}	t_redir_utils;

#endif