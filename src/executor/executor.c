#include "executor.h"
#include "parser.h"
#include "error.h"
#include "minishell.h"

int child;

int is_builtin(t_parser_utils *cmd)
{
	if (strcmp(cmd->cmd_list->data[0], "echo") == 0 ||
		strcmp(cmd->cmd_list->data[0], "pwd") == 0 ||
        strcmp(cmd->cmd_list->data[0], "exit") == 0 ||
        strcmp(cmd->cmd_list->data[0], "env") == 0 ||
        strcmp(cmd->cmd_list->data[0], "cd") == 0 ||
        strcmp(cmd->cmd_list->data[0], "export") == 0 ||
        strcmp(cmd->cmd_list->data[0], "unset") == 0)
		return (0);
	else
		return (1);
}

void execute_builtin(t_parser_utils *cmd)
{
	if (strcmp(cmd->cmd_list->data[0], "echo") == 0)
		cmd_echo(cmd->cmd_list->data);
	else if (strcmp(cmd->cmd_list->data[0], "pwd") == 0)
		cmd_pwd();
	else if (strcmp(cmd->cmd_list->data[0], "exit") == 0)
		cmd_exit();
	else if (strcmp(cmd->cmd_list->data[0], "env") == 0)
		cmd_env(*cmd->env);
	else if (strcmp(cmd->cmd_list->data[0], "cd") == 0)
		cmd_cd(cmd->cmd_list->data, *cmd->env);
	else if (strcmp(cmd->cmd_list->data[0], "export") == 0)
		cmd_export(cmd->env, cmd->cmd_list->data[1]);
	else if (strcmp(cmd->cmd_list->data[0], "unset") == 0)
		cmd_unset(cmd->env, cmd->cmd_list->data[1]);
}

int	executor(t_parser_utils *parser, t_lexer_utils *lexer)
{
	int		fds[lexer->pipe_num * 2];
	int		fd_in;
	int		pipe_num;
	pid_t	pid;
	int		i;
	char	**envp;
	t_cmd	*head;
	
	head = parser->cmd_list;
	i = 0;
	pipe_num = lexer->pipe_num;
	envp = join_key_value(parser->env);
	create_pipes(pipe_num, fds);
	while (parser->cmd_list != NULL)
	{
		pid = fork();
		child = 1;
		signal(SIGQUIT, sigquit_handler);
		//printf("child is %d\n", child);
		if (pid == -1)
			err_msg(ERROR_CHILD);
		else if (pid == 0)
		{
			while (parser->cmd_list->redir)
			{
				if (parser->cmd_list->redir != NULL && parser->cmd_list->redir->redir_type == HERE_DOC)
					here_document(parser->cmd_list, lexer);
				if (parser->cmd_list->redir != NULL && parser->cmd_list->redir->redir_type != DEFAULT)
					fd_in = redirection(parser->cmd_list);
				parser->cmd_list->redir = parser->cmd_list->redir->next;
			}
			if (i != 0)
			{
				if (dup2(fds[i - 2], 0) == -1)
					perror_exit(ERROR_DUP2_IN);
			}
			if (parser->cmd_list->next)
			{
				if (dup2(fds[i + 1], 1) == -1)
					perror_exit(ERROR_DUP2_OUT);
			}
			close_ends(pipe_num, fds);
			// find_usd(parser->cmd_list->data, *parser->env);
			if (is_builtin(parser) == 0)
				execute_builtin(parser);
			else  
			{
				generate_command(parser);
				if (execve(parser->command, parser->cmd_list->data, envp) < 0)
				{
					perror("execve error");
					exit(1);
				}	
			}
			if (fd_in > 0)
				close(fd_in);
		}
		parser->cmd_list = parser->cmd_list->next;
		i += 2;
	}
	parser->cmd_list = head;
	close_ends(pipe_num, fds);
	free_envp(envp);
	return (wait_pipes(pid, pipe_num));
}
