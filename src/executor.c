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

int	wait_pipes(pid_t *pid, int pipe_num)
{
	int	i;
	int	n;
	int	status;

	i = 0;
	n = 0;
	while (i < pipe_num + 1)
	{
		waitpid(pid[n], &status, 0);
		if (WIFEXITED(status) == 0)
		{
			g_global.exit_stat = WEXITSTATUS(status);
			return (0);
		}
		i++;
		n++;
	}
	return (1);
}

// int	forking(t_pipe *pipe, int end[2], t_cmd *cmd_list, int in)
// {
// 	static int	i;

// 	i = 0;
// 	if (pipe->reset == TRUE)
// 	{
// 		i = 0;
// 		pipe->reset = FALSE;
// 	}
// 	pipe->pid[i] = fork();
// 	if (pipe->pid[i] < 0)
// 		err_msg(ERROR_FORK);
// 	if (pipe->pid[i] == 0)
// 		dup_cmd(cmd_list, pipe, end, in);
// 	i++;
// 	return(EXIT_SUCCESS);
// }

// int	check_heredoc(t_lexer_utils *lexer, int end[2], t_cmd *cmd_list)
// {
// 	int	fd_in;

// 	if (lexer->heredoc == TRUE)
// 	{
// 		close(end[0]);
// 		fd_in = open(cmd_list->redir->file_name, O_RDONLY);
// 	}
// 	else
// 		fd_in = end[0];
// 	return (fd_in);
// }

int	executor(t_parser_utils *cmd, t_lexer_utils *lexer, char **envp)
{
	int		fds[lexer->pipe_num * 2];
	int		pipe_num;
	pid_t	*pid;
	int		i;
	int		n;

	i = 0;
	n = 0;
	pipe_num = lexer->pipe_num;
	pid = (pid_t *)malloc(sizeof(pid_t) * (pipe_num + 1));
    if (pid == NULL)
	{
        perror("malloc error");
        exit(EXIT_FAILURE);
    }
	printf("1\n");
	create_pipes(pipe_num, fds);
	printf("2\n");
	while (cmd->cmd_list != NULL)
	{
		printf("3\n");
		pid[n] = fork();
		printf("4\n");
		if (pid[n] == -1)
			err_msg(ERROR_CHILD);
		else if (pid[n] == 0)
		{
			printf("5\n");
			// Redirect stdout to the write end of the current pipe. If it is not the last command
			if (cmd->cmd_list->next)
			{
				printf("dup_out\n");
				if (dup2(fds[i + 1], 1) == -1)
					perror_exit(ERROR_DUP2_OUT);
			}
			//Redirect stdin to the read end of the previous pipe. If not first command and i is no 2 * pipe_num
			if (i > 0)
			{
				printf("dup_in\n");
				if (dup2(fds[i - 2], 0) == -1)
					perror_exit(ERROR_DUP2_IN);
			}
			// compare path and given command
			close_ends(pipe_num, fds);
			cmd->command = command_check(cmd->cmd_dirs, *cmd->cmd_list->data);
			if (execve(cmd->command, cmd->cmd_list->data, envp) < 0)
			{
				perror("execve error");
				exit(1);
			}
		}
		cmd->cmd_list = cmd->cmd_list->next;
		i += 2;
		n++;
	}
	// close parent fds
	close_ends(pipe_num, fds);
	return (wait_pipes(pid, pipe_num));
}
