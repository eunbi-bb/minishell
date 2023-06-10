#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include "../libft/libft.h"
# include "lexer.h"

typedef struct	s_parser_node
{
	char			*str;
	t_types			token;
	int				i;
	struct s_tree	*prev;
	struct s_tree	*next;
}	t_parser_node;

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
	struct s_parser_node	*redir;
	struct s_tokens			*lexer_lst;
	int						num_redir;
	struct s_parser_utils	*utils;
}	t_redir_utils;

#endif