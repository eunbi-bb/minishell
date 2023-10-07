/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 16:10:30 by eucho         #+#    #+#                 */
/*   Updated: 2023/10/07 23:13:29 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "error.h"
#include "minishell.h"

void	cmd_error(char *cmd)
{
	write(STDERR_FILENO, "Minishell: ", 11);
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, ERROR_CMD"\n", ft_strlen(ERROR_CMD) + 1);
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
