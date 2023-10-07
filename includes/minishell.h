#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "parser.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
# include "stdbool.h"

# define PARENT 1
# define CHILD 2
# define HEREDOC 3

// extern int sigint_received;
// extern int child;
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
	APPEND
}	t_types;

typedef	struct	s_tokens
{
	char			*data;
	t_types			token;
	struct s_tokens	*next;
}	t_tokens;

typedef	struct s_lexer_utils
{
	char			*arg;
	t_tokens		*token_list;
	char			*type_arr;
	unsigned int	pipe_num;
	bool			heredoc;
	// char*			heredoc_filename;
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
	t_redir			*redir;
	struct s_cmd	*prev;
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
	bool	reset;
	char	*command;
}	t_parser_utils;

//free_llist.c
void	free_token_list(t_lexer_utils *lexer);
void	free_cmd_list(t_parser_utils *parser);
void	free_env_list(t_parser_utils *parser);
void	destroy_lexer_utils(t_lexer_utils *lexer);
void	destroy_parser_utils(t_parser_utils *parser);
void	free_envp(char **envp);

	/** lexer **/
t_tokens	*new_node(char *data);
t_tokens	*new_token_node(t_types token);
void		add_after(t_tokens **before, t_tokens *new_node);
// bool		match_quotes(char *str);
bool		lexical_analyzer(t_lexer_utils *lexer);
int			arg_divider(t_lexer_utils *lexer, char *str, int i);
int			quotes(char *str, int i);
int			take_tokens(t_lexer_utils *lexer, char *str, int i);
t_env		**createLinkedList(char** envp);
char		*tmp_filename(int i);

int			cmd_echo(char **cmd);
int			cmd_pwd();
void		cmd_exit();
int			cmd_cd(char **path, t_env *env);
void		cmd_export(t_env **head, char *str);

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
int			executor(t_parser_utils *cmd, t_lexer_utils *lexer);
//executor_utils.c
char		**get_cmd_dirs(t_env **envp);
int			generate_command(t_parser_utils *parser);
//redirection.c
int			redirection(t_redir *redir);
//heredoc.c
void		here_document(t_cmd	*cmd);
void		create_heredoc(char *delim, char *filename);
char		*tmp_filename(int i);
//execute_builtins.c
int			is_builtin(t_parser_utils *cmd);
int			execute_builtin(t_parser_utils *cmd);


//env.c
t_env		**createLinkedList(char** envp);
char	**join_key_value(t_env **head);
void find_usd(char **data,  t_env *env);
void cmd_env(t_env *env);
// void sigint_handler(int signal);
char *search_value(char *key, t_env *env);
void cmd_unset(t_env** head,char* key);
// void child_sigint_handler(int signal);
// void	sigquit_handler(int sig);

void	signal_handler(int signal);
void	ctrl_d(void);

#endif