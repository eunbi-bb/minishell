/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 16:13:05 by eucho         #+#    #+#                 */
/*   Updated: 2023/10/13 20:31:15 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "executor.h"
#include "error.h"

char	**get_cmd_dirs(t_env **envp)
{
	char	*tmp;
	char	**dirs;
	t_env	*head;

	head = *envp;
	dirs = NULL;
	while (head)
	{
		if (ft_strncmp(head->key, "PATH", 4) == 0)
		{
			tmp = ft_strdup(head->value + 1);
			dirs = ft_split(tmp, ':');
			free(tmp);
			return (dirs);
		}
		head = head->next;
	}
	return (NULL);
}

char	*command_check(char **path, char *cmd)
{
	char	*command;
	char	*tmp;

	if (path == NULL)
		return (NULL);
	if ((access(cmd, X_OK) == 0))
	{
		return (cmd);
	}
	while (*path)
	{
		tmp = ft_strjoin(*path, "/");
		command = ft_strjoin(tmp, cmd);
		if (command == NULL)
		{
			free(tmp);
			exit(EXIT_FAILURE);
		}
		if (!access(command, F_OK))
			return (command);
		path++;
		free(tmp);
		free(command);
	}
	return (NULL);
}

int	generate_command(t_parser_utils *parser)
{
	t_cmd	*cmd;

	cmd = parser->cmd_list;
	parser->command = command_check(parser->cmd_dirs, *cmd->data);
	if (parser->cmd_dirs == NULL && access(*cmd->data, X_OK) == 0)
		parser->command = *cmd->data;
	if (parser->command == NULL)
	{
		cmd_error(*cmd->data);
		return (EXIT_CMD);
	}
	return (EXIT_SUCCESS);
}
