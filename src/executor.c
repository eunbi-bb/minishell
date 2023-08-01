#include "../includes/executor.h"
#include "../includes/parser.h"
#include "../includes/error.h"

void	create_pipes(int pipe_num, int fds[])
{
	int	i;

	i = 0;
	while (i < pipe_num)
	{
		if (pipe(fds + i * 2) < 0)
		{
			perror("pipe error");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	close_pipes(int pipe_num, int fds[])
{
	int	i;
	i = 0;
	while (i < pipe_num * 2)
	{
		close(fds[i]);
		i++;
	}
}


// t_cmd	*call_expander(t_parser_utils *cmd, t_cmd *cmd_list)
// {
// 	t_tokens	*start;

// 	cmd_list->data = expander(cmd, cmd->data);
// 	start = cmd_list->redir;
// 	while (cmd_list->redir)
// 	{
// 		if (cmd_list->redir->token != HERE_DOC)
// 			cmd_list->redir->data = expander_data(cmd, cmd_list->redir->data);
// 		cmd_list->redir = cmd_list->redir->next;
// 	}
// 	cmd_list->redir = start;
// 	return (cmd);
// }

int	wait_pipes(int *pid, t_error *error, int pid_num)
{
	int	i;
	int	status;

	i = 0;
	while (i < pid_num)
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
	// int		end[2];
	// int		in;
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
		if (pid == 0)
		{
			// if not last command
			if (cmd->cmd_list->next)
			{
				if (dup2(fds[i + 1], 1) < 0)
				{
					perror("dup2");
					exit(EXIT_FAILURE);
				}
			}
			//if not first command and j is no 2 * pipe_num
			if (i != 0)
			{
				if (dup2(fds[i - 2], 0) < 0)
				{
					perror("dup2");
					exit(EXIT_FAILURE);
				}
			}
			close_pipes(pipe_num, fds);
			// compare path and given command
			cmd->command = command_check(path, cmd->cmd_list->data);
			if (execve(cmd->command, cmd->cmd_list) < 0)
			{
				perror("cmd");
				exit(EXIT_FAILURE);
			}
		}
		else if (pid < 0)
		{
			perror("child error");
			exit(EXIT_FAILURE);
		}
		cmd->cmd_list = cmd->cmd_list->next;
		i++;
	}
	wait_pipes(&pipes.pid, &pipes.pipes, pipe_num + 1);
	// in = STDIN_FILENO;
	// pid_num = lexer->pipe_num + 2;
	// if (lexer->pipe_num > 0)
	// 	cmd->pid = malloc(sizeof(int) * pid_num);
	// if (!cmd->pid)
	// 	return (err_msg(ERROR_MEM));
	// while (cmd->cmd_list)
	// {
	// 	if (cmd->cmd_list->next)
	// 		pipe(end);
	// 	// send_heredoc(cmd, cmd->cmd_list);
	// 	forking(&pipe, end, cmd->cmd_list, in);
	// 	close(end[1]);
	// 	if (cmd->cmd_list->prev)
	// 		close(in);
	// 	in = check_heredoc(cmd, end, cmd->cmd_list);
	// 	if (cmd->cmd_list->next)
	// 		cmd->cmd_list = cmd->cmd_list->next;
	// 	else
	// 		break ;
	// }
	// wait_pipes(&pipes.pid, &pipes.pipes, pid_num);
	// cmd->cmd_list = simple_cmd(cmd->cmd_list);
	return (0);
}