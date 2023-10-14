/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_builtins.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 16:12:58 by eucho         #+#    #+#                 */
/*   Updated: 2023/10/13 22:00:34 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

int	is_builtin(t_parser_utils *cmd)
{
	if (strcmp(cmd->cmd_list->data[0], "echo") == 0 \
		|| strcmp(cmd->cmd_list->data[0], "pwd") == 0 \
		|| strcmp(cmd->cmd_list->data[0], "env") == 0 \
		|| strcmp(cmd->cmd_list->data[0], "cd") == 0 \
		|| strcmp(cmd->cmd_list->data[0], "export") == 0 \
		|| strcmp(cmd->cmd_list->data[0], "unset") == 0)
	{
		return (0);
	}
	else
	{
		return (1);
	}
}

int	execute_builtin(t_parser_utils *cmd)
{
	if (strcmp(cmd->cmd_list->data[0], "echo") == 0)
		return cmd_echo(cmd->cmd_list->data);
	else if (strcmp(cmd->cmd_list->data[0], "pwd") == 0)
		return cmd_pwd();
	else if (strcmp(cmd->cmd_list->data[0], "env") == 0)
		return (cmd_env(*cmd->env));
	else if (strcmp(cmd->cmd_list->data[0], "cd") == 0)
		return (cmd_cd(cmd->cmd_list->data, *cmd->env));
	else if (strcmp(cmd->cmd_list->data[0], "export") == 0)
		cmd_export(cmd->env, cmd->cmd_list->data);
	else if (strcmp(cmd->cmd_list->data[0], "unset") == 0)
		return (cmd_unset(cmd->env, cmd->cmd_list->data));
	return (0);
}
