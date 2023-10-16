/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 16:14:05 by eucho         #+#    #+#                 */
/*   Updated: 2023/10/16 20:58:54 by eunbi         ########   odam.nl         */
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

void	wait_pipes(pid_t pid, int pipe_num)
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
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
}
