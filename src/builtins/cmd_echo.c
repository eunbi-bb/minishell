/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_echo.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ssemanco <ssemanco@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/03 11:06:15 by ssemanco      #+#    #+#                 */
/*   Updated: 2023/10/13 23:28:06 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmd(char **cmd)
{
	int	count;

	count = 0;
	while (cmd[count] != NULL)
		count++;
	return (count);
}

int	cmd_echo(char **cmd)
{
	int		new_line;
	int		i;
	int		count;

	i = 1;
	count = count_cmd(cmd);
	new_line = 1;
	if (count > 1 && strcmp(cmd[1], "-n") == 0)
	{
		new_line = 0;
		i = 2;
	}
	while (i < count)
	{
		if (ft_strncmp(cmd[i], "", 1) == 0)
			i++;
		else
			write(1, cmd[i], ft_strlen(cmd[i]));
		if (i < count - 1)
			write(1, " ", 2);
		i++;
	}
	if (new_line)
		write(1, "\n", 1);
	return (0);
}
