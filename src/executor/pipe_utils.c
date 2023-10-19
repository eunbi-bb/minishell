/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 16:14:05 by eucho         #+#    #+#                 */
/*   Updated: 2023/10/19 22:52:44 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/*
*	Wait for a specific child process (pid) to finish its execution
*	and also waits for any other child processes to exit.
*	It stores the exit status of the last child process in a global variable.
*	WIFEXITED macro checks if the child process exited normally.
*	If the child process exited normally, it returns non-zero value otherwise zero.
*/
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
