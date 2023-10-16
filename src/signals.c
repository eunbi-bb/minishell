/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ssemanco <ssemanco@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/30 15:20:36 by ssemanco      #+#    #+#                 */
/*   Updated: 2023/10/16 20:37:32 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
*	SIGINT	= ctrl + c
*	SIGQUIT = ctrl + /
*
*	|= (ECHOCTL) = showing control keys
*	&= ~(ECHOCTL) = Not showing control keys
*/


#include "minishell.h"

void	return_prompt(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	backslash(int sig)
{
	if (sig == SIGQUIT)
	{
		write(STDERR_FILENO, "Quit (core dumped)\n", 19);
		g_exit_status = 131;
	}
}

void	ctrl_c(int sig)
{
	if (sig == SIGINT)
	{
		write(STDIN_FILENO, "\n", 1);
		g_exit_status = 130;
	}
}

void	signal_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		exit(1);
	}
}

void	signal_handler(int sig)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
	if (sig == PARENT)
	{
		signal(SIGINT, return_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (sig == CHILD)
	{
		tcgetattr(STDIN_FILENO, &term);
		term.c_lflag |= (ECHOCTL);
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, backslash);
	}
	else if (sig == HEREDOC)
	{
		signal(SIGINT, signal_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
}
