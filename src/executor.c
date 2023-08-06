#include "../includes/executor.h"
#include "../includes/parser.h"
#include "../includes/error.h"

void	create_pipes(int pipe_num, int fds[])
{
	int	i;

	i = 0;
	while (i < pipe_num)
	{
		if (pipe(fds + (i * 2)) == -1)
		{
			perror("pipe error");
			printf("%d", errno);
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

int	wait_pipes(int *pid, t_error *error, int pipe_num)
{
	int	i;
	int	status;

	i = 0;
	while (i < pipe_num)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	waitpid(pid[i], &status, 0);
	if (WIFEXITED(status) == 0)
		error->error_status = WEXITSTATUS(status);
	return (EXIT_SUCCESS);
}

int	forking(t_pipe *pipe, int end[2], t_cmd *cmd_list, int in)
{
	static int	i;

	i = 0;
	if (pipe->reset == TRUE)
	{
		i = 0;
		pipe->reset = FALSE;
	}
	pipe->pid[i] = fork();
	if (pipe->pid[i] < 0)
		err_msg(ERROR_FORK);
	if (pipe->pid[i] == 0)
		dup_cmd(cmd_list, pipe, end, in);
	i++;
	return(EXIT_SUCCESS);
}

int	check_heredoc(t_parser_utils *cmd, int end[2], t_cmd *cmd_list)
{
	int	fd_in;

	if (cmd_list->redir->heredoc)
	{
		close(end[0]);
		fd_in = open(cmd_list->redir->file_name, O_RDONLY);
	}
	else
		fd_in = end[0];
	return (fd_in);
}

char	*command_check(char **path, char *cmd)
{
	char	*command;
	char	*tmp;

	if (path == NULL)
		return (NULL);
	if ((access(cmd, X_OK) == 0))
	{
		command = cmd;
		return (command);
	}
	while (*path)
	{
		tmp = ft_strjoin(*path, "/");
		command = ft_strjoin(tmp, cmd);
		if (command == NULL)
		{
			free(tmp);
			exit(EXIT_FAILURE);
		}
		if (!access(command, F_OK))
			return (command);
		path++;
		free(tmp);
		free(command);
	}
	return (NULL);
}

int	executor(t_parser_utils *cmd, t_lexer_utils *lexer)
{
	t_pipe	pipes;
	int	fds[lexer->pipe_num * 2];
	int		pipe_num;
	pid_t	pid;
	int		i;

	i = 0;
	pipe_num = lexer->pipe_num;
	create_pipes(pipe_num, fds);
	while (cmd->cmd_list != NULL)
	{
		pid = fork();
		if (pid < 0)
			err_msg(ERROR_CHILD);
		else if (pid == 0)
		{
			// Redirect stdout to the write end of the current pipe. If it is not the last command
			if (cmd->cmd_list->next)
			{
				if (dup2(fds[i + 1], 1) == -1)
					perror_exit(ERROR_DUP2_OUT);
			}
			//Redirect stdin to the read end of the previous pipe. If not first command and i is no 2 * pipe_num
			if (i > 0)
			{
				if (dup2(fds[i - 2], 0) == -1)
					perror_exit(ERROR_DUP2_IN);
			}
			// compare path and given command
			close_ends(pipe_num, fds);
			cmd->command = command_check(cmd->env, cmd->cmd_list->data);
			if (execve(cmd->command, cmd->cmd_list) < 0)
			{
				perror("excve error");
				exit(1);
			}
		}
		cmd->cmd_list = cmd->cmd_list->next;
		i += 2;
	}
	// close parent fds
	close_ends(pipe_num, fds);
	wait_pipes(&pipes.pid, &pipes.pipes, pipe_num + 1);
	return (0);
}
