/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/18 15:20:14 by eucho         #+#    #+#                 */
/*   Updated: 2023/10/27 22:30:50 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>

# define PARENT 1
# define CHILD 2
# define HEREDOC 3

extern int	g_exit_status;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef enum types
{
	DEFAULT = -1,
	PIPE,
	LESSER,
	GREATER,
	HERE_DOC,
	APPEND
}	t_types;

typedef struct s_tokens
{
	char			*data;
	t_types			token;
	struct s_tokens	*next;
}	t_tokens;

typedef struct s_lexer
{
	char			*arg;
	t_tokens		*token_list;
	char			*type_arr;
	unsigned int	pipe_num;
	bool			heredoc;
}	t_lexer;

typedef struct s_redir
{
	char			*file_name;
	t_types			redir_type;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**data;
	t_types			type;
	t_redir			*redir;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_parser
{
	t_cmd	*cmd_list;
	char	*args;
	t_env	*env;
	char	**envp;
	char	**cmd_dirs;
	int		pipes;
	int		pid;
	char	*command;
	int		cmd_exit_code;
}	t_parser;

//	signal.c
void		signal_handler(int sig);
void		signal_heredoc(int sig);

/***** parser *****/
//	parser.c
void		parser(t_lexer *lexer, t_parser *parser);
//	cmd_node_utils.c
t_cmd		*create_cmd_node(void);
void		add_after_cmd(t_cmd **before, t_cmd *new_node);
//	redir_node_utils.c
t_redir		*create_redir_node(void);
void		add_after_redir(t_redir **before, t_redir *new_node);
/***** lexer *****/
//	lexer.c
bool		lexical_analyzer(t_lexer *lexer);
void		determine_expanding(t_lexer *lexer, t_parser *parser);
void		free_tmp(char *tmp);
//	lexer_utils.c
bool		is_whitespace(char c);
int			skip_whitespace(char *s, int i);
int			is_token(int c);
bool		match_quotes(char *str);
int			next_quote(char *str, int i);
//	dollar_sign.c
void		find_dollar(char *str, t_lexer *lexer, char quote);
//	node_utils.c
t_tokens	*new_token_node(char *data, t_types token);
void		add_after(t_tokens **before, t_tokens *new_node);
void		add_to(t_tokens *before, char *data);
void		add_to_last(t_tokens **before, char *data);
/***** free *****/
//	free_destroy.c
void		free_prev_line(t_lexer *lexer, char *line);
void		free_envp(char **envp);
void		free_cmd_dirs(t_parser *parser);
void		destroy_lexer_parser(t_lexer *lexer, t_parser *parser);
void		reset(t_lexer *lexer, t_parser *parser, char *line);
//	free_llist.c
void		free_token_list(t_lexer *lexer);
void		free_redir_list(t_cmd *cmd);
void		free_cmd_list(t_parser *parser);
void		free_env_list(t_parser *parser);
/***** executor *****/
//	command_utils.c
char	**get_cmd_dirs(t_env *envp);
int			execute_command(t_parser *parser);
//	execute_builtins.c
int			is_builtin(t_parser *cmd);
int			execute_builtin(t_parser *cmd);
//	executor.c
void		setup_executor(t_lexer *lexer, t_parser *parser);
//	heredoc.c
void		here_document(t_cmd	*cmd);
//	pipe_utils.c
void		create_pipes(int pipe_num, int fds[]);
void		close_ends(int pipe_num, int fds[]);
void		wait_pipes(pid_t pid, int pipe_num);
//	redirection.c
int			execute_redir(t_parser *parser, t_redir *redir, int fd_in);

int			cmd_echo(char **cmd);
int			cmd_pwd(void);
int			cmd_cd(char **path, t_env *env);
int			cmd_export(t_env *head, char **str);
int			cmd_unset(t_env *head, char **key);
int			cmd_exit(char **input);
int			var_exist(char *key, t_env *env);
void		print_list(t_env *head);
t_env		*merge_sort(t_env *head);
void		free_sorted(t_env *head);

//env.c
void	create_env_list(t_parser *parser, char** envp);
char	**join_key_value(t_env *head);
int 		cmd_env(t_env *env);
char	*expand(char *str, t_env *env);
char		*search_value(char *key, t_env *env);

int			count_cmd(char **cmd);
#endif