#include "../../includes/minishell.h"
#include "../../includes/parser.h"
#include "../../includes/executor.h"
#include "../../includes/error.h"

char	**get_cmd_dirs(t_env **envp)
{
	char	*tmp;
	char	**dirs;

	dirs = NULL;
	while (envp)
	{
		if (ft_strncmp((*envp)->key, "PATH", 4) == 0)
		{
			tmp = ft_strdup((*envp)->value + 1);
			dirs = ft_split(tmp, ':');
			return (dirs);
		}
		(*envp) = (*envp)->next;
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

void	generate_command(t_parser_utils *cmd)
{
	cmd->command = command_check(cmd->cmd_dirs, *cmd->cmd_list->data);
	if (cmd->cmd_dirs == NULL && access(*cmd->cmd_list->data, X_OK) == 0)
		cmd->command = *cmd->cmd_list->data;
	if (cmd->command == NULL)
	{
		cmd_error(*cmd->cmd_list->data);
		// free_child(pipex);
		exit(EXIT_CMD);
	}
}
