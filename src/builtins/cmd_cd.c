/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_cd.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ssemanco <ssemanco@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/07 11:36:32 by ssemanco      #+#    #+#                 */
/*   Updated: 2023/10/29 16:49:36 by ssemanco      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "error.h"

void	env_replace_var(char *key, t_env *env, char *path)
{
	size_t	len;

	len = ft_strlen(key);
	while (env)
	{
		if (ft_strncmp(key, env->key, len) == 0)
		{
			free(env->value);
			env->value = ft_strdup(path);
			if (!env->value)
				perror_exit("malloc fail");
		}
		env = env->next;
	}
}

void	replace_paths(t_env *env)
{
	char	*pwd;
	char	*new_pwd;

	pwd = search_value("PWD", env);
	env_replace_var("OLDPWD", env, pwd);
	new_pwd = getcwd(NULL, 0);
	if (new_pwd == NULL)
	{
		write(STDERR_FILENO, "cd: error retrieving current directory:", 39);
		write(STDERR_FILENO, "getcwd:cannot access parent directories:", 40);
		write(STDERR_FILENO, "No such file or directory\n", 26);
		return ;
	}
	env_replace_var("PWD", env, new_pwd);
	free(new_pwd);
}

int	cd_error(void)
{
	write(STDERR_FILENO, "cd: too many arguments\n", 23);
	return (1);
}

int	cmd_cd(char **path, t_env *env)
{
	char	*home;

	if (count_cmd(path) > 2)
		return (cd_error());
	if (!path[1])
	{
		home = search_value("HOME=", env);
		if (chdir(home) == -1)
		{
			perror("cd ");
			return (1);
		}
		replace_paths(env);
		return (0);
	}
	else
	{
		if (chdir(path[1]) == -1)
		{
			perror("cd ");
			return (1);
		}
		replace_paths(env);
		return (0);
	}
}
