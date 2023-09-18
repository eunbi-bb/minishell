/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_cd.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ssemanco <ssemanco@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/07 11:36:32 by ssemanco      #+#    #+#                 */
/*   Updated: 2023/09/17 23:32:00 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/error.h"

void env_replace_var(char *key, t_env *env, char *path)
{
    size_t len;

    len = ft_strlen(key);
    while (env)
    {

        if(ft_strncmp(key, env->key, len) == 0)
        {
			free(env->value);
			env->value = ft_strdup(path);
			if (!env->value)
				perror_exit("malloc fail");
		}
        env = env->next;
    }
}

int cmd_cd(char **path, t_env *env) 
{
	char *pwd;
	char *new_pwd;
	char *home;

	if (!path[1])
	{
		home = search_value("HOME=", env);
		printf("%s\n", home);
		if (chdir(home) == -1) {
			printf("erorr cd invalid\n");
		}
		pwd = search_value("PWD", env);
		env_replace_var("OLDPWD", env, pwd);
		new_pwd = getcwd(NULL, 0);
		env_replace_var("PWD", env, new_pwd);
		free(new_pwd);
		return (0);
	}
	else
	{
		if (chdir(path[1]) == -1) {
			printf("erorr cd\n");
		}
			// error
		pwd = search_value("PWD", env);
		env_replace_var("OLDPWD", env, pwd);
		new_pwd = getcwd(NULL, 0);
		env_replace_var("PWD", env, new_pwd);
		free(new_pwd);
		return (0);
	}
	return (1);
}
