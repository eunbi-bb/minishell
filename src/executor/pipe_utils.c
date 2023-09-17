#include "../../includes/minishell.h"
#include "../../includes/executor.h"

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
