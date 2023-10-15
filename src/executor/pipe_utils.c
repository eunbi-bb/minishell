/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 16:14:05 by eucho         #+#    #+#                 */
/*   Updated: 2023/10/15 15:53:49 by eucho         ########   odam.nl         */
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

void	wait_pipes(pid_t pid, int pipe_num, int built_in)
{
	int	i;
	int	status;	

	i = 0;
	waitpid(pid, &status, 0);
	while (i < pipe_num + 1)
	{
		wait(&status);
		i++;
	}
	if (built_in == 0)
		g_exit_status = WEXITSTATUS(status);
}
