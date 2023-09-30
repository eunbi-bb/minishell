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

int	execute_redir(t_parser_utils *parser, t_lexer_utils *lexer, t_redir *redir)
{
	int	fd_in;
	t_redir	*head;

	head = redir;
	fd_in = 0;
	while (redir)
	{
		if (redir != NULL && redir->redir_type == HERE_DOC)
			here_document(parser->cmd_list, lexer);
		if (redir != NULL && redir->redir_type != DEFAULT)
			fd_in = redirection(parser->cmd_list);
		redir = redir->next;
	}
	redir = head;
	return (fd_in);
}

int	executor(t_parser_utils *parser, t_lexer_utils *lexer)
{
	int		fds[lexer->pipe_num * 2];
	int		fd_in;
	pid_t	pid;
	int		i;
	t_cmd	*head;
	
	head = parser->cmd_list;
	i = 0;
	create_pipes(lexer->pipe_num, fds);
	while (parser->cmd_list != NULL)
	{
		pid = fork();
		child = 1;
		signal(SIGQUIT, sigquit_handler);
		if (pid == -1)
			err_msg(ERROR_CHILD);
		else if (pid == 0)
		{
			fd_in = execute_redir(parser, lexer, parser->cmd_list->redir);
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
			close_ends(lexer->pipe_num, fds);
			// find_usd(parser->cmd_list->data, *parser->env);
			if (is_builtin(parser) == 0)
			{
				execute_builtin(parser);
				return (0);
			}
			else  
			{
				if (generate_command(parser) == EXIT_CMD)
					return (EXIT_CMD);
				if (execve(parser->command, parser->cmd_list->data, parser->envp) < 0)
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
	close_ends(lexer->pipe_num, fds);
	return (wait_pipes(pid, lexer->pipe_num));
}
