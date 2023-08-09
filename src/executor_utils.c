#include "../includes/minishell.h"
#include "../includes/parser.h"

char	**get_cmd_dirs(t_env *envp)
{
	char	*tmp;
	char	**dirs;

	dirs = NULL;
	while (envp)
	{
		if (ft_strncmp(envp->key, "PATH", 4) == 0)
		{
			tmp = ft_strdup(envp->value + 1);
			dirs = ft_split(tmp, ':');
			return (dirs);

		}
		envp = envp->next;
	}
	return (NULL);
}

char	*command_check(char *path, char *cmd)
{
	char	*command;
	char	*tmp;

	if (path == NULL)
		return (NULL);
	if ((access(cmd, X_OK) == 0))
	{
		command = cmd;
		return (command);
	}
	while (*path)
	{
		tmp = ft_strjoin(path, "/");
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