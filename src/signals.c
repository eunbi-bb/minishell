/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ssemanco <ssemanco@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/30 15:20:36 by ssemanco      #+#    #+#                 */
/*   Updated: 2023/10/07 18:25:07 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
*	SIGINT	= ctrl + c
*	SIGQUIT = ctrl + /
*
*
*
*
*
*
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
		g_exit_status = 1;
	}
}

void	backslash(int sig)
{
	if (sig == SIGQUIT)
	{
		write(STDERR_FILENO, "Quit: ", 6);
		ft_putnbr_fd(sig, STDERR_FILENO);
		write(STDERR_FILENO, "\n", 1);
		g_exit_status = 128 + sig;
	}
}

void	ctrl_c(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		g_exit_status = 128 + sig;
	}
}

void	signal_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		g_exit_status = 1;
		exit(g_exit_status);
	}
}

void	signal_handler(int sig)
{
	struct termios	ter;

	tcgetattr(STDIN_FILENO, &ter);
	ter.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &ter);
	if (sig == PARENT)
	{
		signal(SIGINT, return_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (sig == CHILD)
	{
		tcgetattr(STDIN_FILENO, &ter);
		ter.c_lflag |= (ECHOCTL);
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &ter);
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, backslash);
	}
	else if (sig == HEREDOC)
	{
		signal(SIGINT, signal_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
}


// void sigint_handler(int signal) 
// {	
// 	sigint_received = 1;
// 	if (child == 1) //in cmd
// 	{
// 		child = 0;
// 		printf("\n");
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 		rl_done = 1;
// 		return ;
// 	}
//     rl_on_new_line();
// 	printf("\n");
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// 	(void)signal;
// }

// void	sigquit_handler(int sig)
// {
// 	ft_putstr_fd("Quit: ", STDERR_FILENO);
// 	ft_putnbr_fd(sig, STDERR_FILENO);
// 	ft_putchar_fd('\n', STDERR_FILENO);
// }

