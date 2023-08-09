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
			int i = 0;
			while (dirs[i])
			{
				printf("%s\n", dirs[i]);
				i++;
			}
			return (dirs);
		}
		envp = envp->next;
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
		printf("tmp : %s\n", tmp);
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
