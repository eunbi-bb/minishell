#include "../includes/executor.h"
#include "../includes/parser.h"
#include "../includes/error.h"
#include "../includes/minishell.h"

void	create_pipes(int pipe_num, int fds[])
{
	int	i;

	i = 0;
	while (i < pipe_num)
	{
		if (pipe(fds + (i * 2)) == -1)
		{
			perror("pipe error");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	close_ends(int pipe_num, int fds[])
{
	int	i;
	i = 0;
	while (i < pipe_num * 2)
	{
		close(fds[i]);
		i++;
	}
}

int	wait_pipes(pid_t pid, int pipe_num)
{
	int	i;
	int	status;

	i = 0;
	while (i < pipe_num + 1)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) == 0)
		{
			return (WEXITSTATUS(status));
		}
		i++;
	}
	return (0);
}

int	executor(t_parser_utils *cmd, t_lexer_utils *lexer)
{
	int		fds[lexer->pipe_num * 2];
	int		fd_in;
	int		pipe_num;
	pid_t	pid;
	int		i;
	int		n;

	i = 0;
	n = 0;
	pipe_num = lexer->pipe_num;
	create_pipes(pipe_num, fds);
	while (cmd->cmd_list != NULL)
	{
		printf("exec\n");
		pid = fork();
		if (pid == -1)
			err_msg(ERROR_CHILD);
		else if (pid == 0)
		{
			if (cmd->cmd_list->redir != NULL && cmd->cmd_list->redir->redir_type == HERE_DOC)
			{
				printf("heredoc\n");
				here_document(cmd->cmd_list, lexer);
			}
			if (cmd->cmd_list->redir != NULL && cmd->cmd_list->redir->redir_type >= 1)
			{
				printf("redir\n");
				fd_in = redirection(cmd->cmd_list);
			}
			if (i != 0)
			{
				if (dup2(fds[i - 2], 0) == -1)
					perror_exit(ERROR_DUP2_IN);
			}
			if (cmd->cmd_list->next)
			{
				if (dup2(fds[i + 1], 1) == -1)
					perror_exit(ERROR_DUP2_OUT);
			}
			close_ends(pipe_num, fds);

			// int i = 0;
			// while (cmd->cmd_list->data[i])
			// {
			// 	printf("cmd->cmd_list->data[%d] = %s\n", i , cmd->cmd_list->data[i]);
			// 	i++;
			// }
			cmd->command = command_check(cmd->cmd_dirs, *cmd->cmd_list->data);
			// printf("command : %s\n", cmd->command);
			// int i = 0;
			// while (cmd->cmd_list->data[i])
			// {
			// 	printf("cmd->cmd_list->data[%d] = %s\n", i , cmd->cmd_list->data[i]);
			// 	i++;
			// }
			if (execve(cmd->command, cmd->cmd_list->data, (char* const*)cmd->env) < 0)
			{
				perror("execve error");
				exit(1);
			}
			if (fd_in > 0)
				close(fd_in);
		}
		cmd->cmd_list = cmd->cmd_list->next;
		i += 2;
		n++;
	}
	close_ends(pipe_num, fds);
	return (wait_pipes(pid, pipe_num));
}
