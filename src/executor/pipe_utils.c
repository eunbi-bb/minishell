/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 16:14:05 by eucho         #+#    #+#                 */
/*   Updated: 2023/10/13 21:42:07 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

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
	int exitcode;

	i = 0;
	exitcode = 0;
	waitpid(pid, &status, 0);
	exitcode = WEXITSTATUS(status);
	while (i < pipe_num + 1)
	{
		wait(&status);
		i++;
	}

	return (exitcode);
}
