/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_builtins.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 16:12:58 by eucho         #+#    #+#                 */
/*   Updated: 2023/10/18 14:33:14 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_parser *cmd)
{
	if (strcmp(cmd->cmd_list->data[0], "echo") == 0 \
		|| strcmp(cmd->cmd_list->data[0], "pwd") == 0 \
		|| strcmp(cmd->cmd_list->data[0], "env") == 0 \
		|| strcmp(cmd->cmd_list->data[0], "cd") == 0 \
		|| strcmp(cmd->cmd_list->data[0], "export") == 0 \
		|| strcmp(cmd->cmd_list->data[0], "unset") == 0 \
		|| strcmp(cmd->cmd_list->data[0], "exit") == 0)
	{
		return (0);
	}
	else
	{
		return (1);
	}
}

int	execute_builtin(t_parser *cmd)
{
	if (strcmp(cmd->cmd_list->data[0], "echo") == 0)
		return (cmd_echo(cmd->cmd_list->data));
	else if (strcmp(cmd->cmd_list->data[0], "pwd") == 0)
		return (cmd_pwd());
	else if (strcmp(cmd->cmd_list->data[0], "env") == 0)
		return (cmd_env(*cmd->env));
	else if (strcmp(cmd->cmd_list->data[0], "cd") == 0)
		return (cmd_cd(cmd->cmd_list->data, *cmd->env));
	else if (strcmp(cmd->cmd_list->data[0], "export") == 0)
		return (cmd_export(cmd->env, cmd->cmd_list->data));
	else if (strcmp(cmd->cmd_list->data[0], "unset") == 0)
		return (cmd_unset(cmd->env, cmd->cmd_list->data));
	return (0);
}
