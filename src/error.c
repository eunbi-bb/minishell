/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 16:10:30 by eucho         #+#    #+#                 */
/*   Updated: 2023/10/14 18:25:41 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "error.h"
#include "minishell.h"

bool	is_str_whitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!is_whitespace(str[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	input_check(char *str)
{
	int len;

	len = ft_strlen(str);
	if (len > 0 && (str[len - 1] == '<' || str[len - 1] == '>'))
	{
		write(STDERR_FILENO, ERROR_NEWLINE, ft_strlen(ERROR_NEWLINE));
		write(STDERR_FILENO, "\n", 1);
		g_exit_status = 2;
		return (false);
	}
	else if (str[0] == '|')
	{
		write(STDERR_FILENO, ERROR_PIPE, ft_strlen(ERROR_PIPE));
		write(STDERR_FILENO, "\n", 1);
		g_exit_status = 2;
		return(false);
	}
	else if (is_str_whitespace(str) == true || match_quotes(str) == false)
	{
		g_exit_status = 0;
		return (false);
	}
	return (true);
}

void	cmd_error(char *cmd)
{
	write(STDERR_FILENO, "Minishell: ", 11);
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, ERROR_CMD"\n", ft_strlen(ERROR_CMD) + 1);
	g_exit_status = 127;
}

int	err_msg(char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n", 1);
	exit (EXIT_FAILURE);
}

void	perror_exit(char *str)
{
	perror(str);
	exit(errno);
}

