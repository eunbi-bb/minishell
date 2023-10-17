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
    char	*key;
    char	*value;
    struct s_env *next;
}               t_env;

typedef enum types
{
	DEFAULT = -1,
	PIPE,
	LESSER,
	GREATER,
	HERE_DOC,
	APPEND,
	DOLLAR,
	QUESTION
}	t_types;

typedef	struct	s_tokens
{
	char	*data;
	t_types	token;
	bool	s_quote;
	bool	d_quote;
	struct s_tokens	*next;
}	t_tokens;

typedef	struct s_lexer_utils
{
	char			*arg;
	t_tokens		*token_list;
	char			*type_arr;
	unsigned int	pipe_num;
	bool			heredoc;
}	t_lexer_utils;

typedef struct s_redir
{
	char		*file_name;
	t_types		redir_type;
	struct s_redir *next;
}	t_redir;

typedef struct	s_cmd
{
	char			**data;
	t_types			type;
	t_redir			*redir;
	struct s_cmd	*next;
}	t_cmd;

typedef struct	s_parser_utils
{
	t_cmd	*cmd_list;
	char	*args;
	t_env	**env;
	char	**envp;
	char	**cmd_dirs;
	int		pipes;
	int		pid;
	char	*command;
}	t_parser_utils;

//free_llist.c
void	reset(t_lexer_utils *lexer, t_parser_utils *parser, char *line);
void	free_token_list(t_lexer_utils *lexer);
void	free_cmd_list(t_parser_utils *parser);
void	free_env_list(t_parser_utils *parser);
void	destroy_lexer_utils(t_lexer_utils *lexer);
void	destroy_parser_utils(t_parser_utils *parser);
void	free_envp(char **envp);
void	free_prev_line(t_lexer_utils *lexer, char *line);
void	free_cmd_dirs(t_parser_utils *parser);

	/** lexer **/
t_tokens	*new_node(char *data);
t_tokens	*new_token_node(char *data, t_types token, char quote);
void		add_after(t_tokens **before, t_tokens *new_node);
void		find_dollar(char *str, t_lexer_utils *lexer, char quote);
bool		match_quotes(char *str);
bool		is_whitespace(char c);
int			skip_whitespace(char *s, int i);
int			is_token(int c);
bool		lexical_analyzer(t_lexer_utils *lexer);
int			arg_divider(t_lexer_utils *lexer, char *str, int i, char quote);
int			quotes(char *str, int i, char quote);
int			take_tokens(t_lexer_utils *lexer, char *str, int i);
t_env		**createLinkedList(char** envp);
char		*tmp_filename(int i);

int			cmd_echo(char **cmd);
int			cmd_pwd();
void		cmd_exit();
int			cmd_cd(char **path, t_env *env);
int			cmd_export(t_env **head, char **str);
int			var_exist(char *key, t_env *env);
void		print_list(t_env *head);
t_env		*merge_sort(t_env *head);

	/** parser **/
//parser.c
void		parser(t_lexer_utils *lexer, t_parser_utils *parser);
int			count_args(t_tokens	*lexer);
//cmd_node_utils.c
t_cmd		*create_cmd_node(void);
void		add_after_cmd(t_cmd **before, t_cmd *new_node);
//redir_node_utils.c
t_redir		*create_redir_node(void);
void		add_after_redir(t_redir **before, t_redir *new_node);

	/** executor **/
//executor.c
void	executor(t_parser_utils *parser, t_lexer_utils *lexer);
int	execute_redir(t_parser_utils *parser, t_redir *redir);
//executor_utils.c
char		**get_cmd_dirs(t_env **envp);
int			generate_command(t_parser_utils *parser);
//redirection.c
int			redirection(t_redir *redir);
int	create_outfile(t_redir *redir);
//heredoc.c
void		here_document(t_cmd	*cmd);
void		create_heredoc(char *delim, char *filename);
char		*tmp_filename(int i);
//execute_builtins.c
int			is_builtin(t_parser_utils *cmd);
int			execute_builtin(t_parser_utils *cmd);
//pipe_utils.c
void		create_pipes(int pipe_num, int fds[]);
void		close_ends(int pipe_num, int fds[]);
void		wait_pipes(pid_t pid, int pipe_num);


//env.c
t_env		**createLinkedList(char** envp);
char		**join_key_value(t_env **head);
int			cmd_env(t_env *env);
// void sigint_handler(int signal);
char		*search_value(char *key, t_env *env);
int			cmd_unset(t_env** head,char** key);
// void child_sigint_handler(int signal);
// void	sigquit_handler(int sig);

void		signal_handler(int signal);
void		ctrl_d(void);

void		expand(t_tokens *token_list,  t_env *env);

#endif