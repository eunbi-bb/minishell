/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_exit.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/22 21:22:09 by eucho         #+#    #+#                 */
/*   Updated: 2023/10/28 19:19:58 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_str_digits(char *str)
{
	int	i;

	i = 0;
	if (str == NULL || *str == '\0')
		return (false);
	if (str[0] == '-')
		i++;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

static void	exit_err(int i, char *data)
{
	if (i == 1)
	{
		write(STDOUT_FILENO, "exit\nMinishell:", 16);
		write(STDERR_FILENO, " too many arguments\n", 20);
	}
	else if (i == 2)
	{
		write(STDOUT_FILENO, "exit\nMinishell: exit: ", 16);
		write(STDERR_FILENO, data, ft_strlen(data));
		write(STDERR_FILENO, ": numeric argument required\n", 27);
	}
	exit(i);
}

int	cmd_exit(char **data)
{
	int	exit_c;

	if (data[1])
	{
		if (is_str_digits(data[1]) == false)
			exit_err(2, data[1]);
		else
		{
			if (count_cmd(data) > 2)
				exit_err(1, NULL);
			else
			{
				exit_c = ft_atoi(data[1]);
				write(STDOUT_FILENO, "exit\n", 5);
				exit(exit_c % 256);
			}
		}
	}
	write(STDOUT_FILENO, "exit\n", 5);
	exit (0);
}
