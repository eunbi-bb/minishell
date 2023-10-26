/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ssemanco <ssemanco@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/30 15:20:36 by ssemanco      #+#    #+#                 */
/*   Updated: 2023/10/23 17:54:18 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
*	SIGINT	= ctrl + c
*	SIGQUIT = ctrl + /
*	|= (ECHOCTL) = showing control keys
*	&= ~(ECHOCTL) = Not showing control keys
*/
#include "minishell.h"

static void	return_prompt(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	backslash(int sig)
{
	if (sig == SIGQUIT)
	{
		write(STDERR_FILENO, "Quit (core dumped)\n", 19);
		g_exit_status = 131;
	}
}

static void	ctrl_c(int sig)
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
		write(STDOUT_FILENO, "> ^C\n", 5);
		exit(0);
	}
}

/*
*	termios	: data structure used to configure terminal I/O settings,
*	tcgetattr(STDIN_FILENO, &term) : To get the current terminal settings.
*			It retrieves the current terminal attributes associated 
*			with the standard input and stores them in &term.
*	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term) : Call sets the terminal attributes
*			for the standard input to the values stored in the term structure.
*	The 'TCSAFLUSH' flag indicates that the change should occur after all output 
*			is transmitted, and all input received is processed.
*/
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
