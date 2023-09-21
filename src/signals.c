/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ssemanco <ssemanco@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/30 15:20:36 by ssemanco      #+#    #+#                 */
/*   Updated: 2023/09/17 13:31:26 by ssemanco      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void sigint_handler(int signal) 
{	
	sigint_received = 1;
	if (child == 1) //in cmd
	{
		child = 0;
		printf("\n");
		rl_replace_line("", 0);
		rl_redisplay();
		rl_done = 1;
		return ;
	}
    rl_on_new_line();
	printf("\n");
	rl_replace_line("", 0);
	rl_redisplay();
	(void)signal;
}

void	sigquit_handler(int sig)
{
	ft_putstr_fd("Quit: ", STDERR_FILENO);
	ft_putnbr_fd(sig, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

