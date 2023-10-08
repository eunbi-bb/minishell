/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: eunbi <eunbi@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 23:16:29 by eunbi         #+#    #+#                 */
/*   Updated: 2023/10/07 20:04:33 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_input_mode(struct termios *org_term)
{
	tcgetattr(STDIN_FILENO, org_term);
}

void	set_input_mode(struct termios *new_term)
{
	tcgetattr(STDIN_FILENO, new_term);
	new_term->c_lflag &= ~(ICANON | ECHO);
	new_term->c_cc[VMIN] = 1;
	new_term->c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, new_term);
}

void reset_input_mode(struct termios *org_term)
{
	tcsetattr(STDIN_FILENO, TCSANOW, org_term);
}

void ctrl_d(void)
{
	struct termios org_term;
	struct termios new_term;
	int	ch = 0;
	int	idx = -1;

	save_input_mode(&org_term);
	set_input_mode(&new_term);
	while (read(0, &ch, 1) > 0)
	{
		if (ch == 4)
		{
			if (idx == -1)
				exit(0);
			else
				continue;
		}
		else if (ch == 127)
		{
			if (idx >= 0)
			{
				--idx;
				write(0, "\b \b", 3);
			}
		}
		else if (ch == '\n')
			break;
		else
		{
			++idx;
			write(0, &ch, sizeof(int));
		}
		ch = 0;
	}
	reset_input_mode(&org_term);
}