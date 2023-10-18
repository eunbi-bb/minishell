/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ssemanco <ssemanco@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/31 14:20:34 by ssemanco      #+#    #+#                 */
/*   Updated: 2023/10/18 19:53:23 by ssemanco      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "error.h"

void	free_data(t_data *data)
{
	if (data->eq_sign != NULL)
		free(data->eq_sign);
	if (data->env != NULL)
		free(data->env);
	if (data->key != NULL)
		free(data->key);
	if (data->value != NULL)
		free(data->value);
	free(data);
}

t_env	*create_node(char *key, char *value)
{
	t_env	*new_node;

	new_node = ft_calloc(1, sizeof(t_env));
	if (new_node == NULL)
		perror_exit("malloc fail");
	new_node->key = ft_strdup(key);
	if (new_node->key == NULL)
		perror_exit("malloc fail");
	free(key);
	new_node->value = ft_strdup(value);
	if (new_node->value == NULL)
		perror_exit("malloc fail");
	free(value);
	new_node->next = NULL;
	return (new_node);
}

int	cmd_env(t_env *env)
{
	t_env	*head;

	head = env;
	while (env)
	{
		printf("%s%s\n", env->key, env->value);
		env = env->next;
	}
	env = head;
	return (0);
}

// t_env **create_link_list(char** envp, t_data *data)
// {
// 	t_env	**head;
// 	t_env	*current;
// 	int		i;

// 	head = NULL;
// 	current = NULL;
// 	i = 0;
// 	while (envp[i] != NULL)
// 	{
// 		data->env = envp[i];
// 		data->eq_sign = ft_strchr(data->env, '=');
// 		if (data->eq_sign == NULL)
// 		{
// 			i++;
// 			continue;
// 		}
// 		data->key_len = data->eq_sign - data->env + 1;
// 		data->key = ft_strndup(data->env, data->key_len);
// 		data->value = ft_strdup(data->eq_sign + 1);
//  		data->new_node = create_node(data->key, data->value);
// 		if (head == NULL)
// 		{
// 			head = ft_calloc(1, sizeof(t_env*));
// 			*head = data->new_node;
// 			current = data->new_node;
// 		}
// 		else 
// 		{
// 			current->next = data->new_node;
// 			current = data->new_node;
// 		}
// 		i++;
// 	}
// 	//free_data(data);
// 	return head;
// }

t_env	*create_node_from_env(char *env, t_data *data)
{
	data->env = env;
	data->eq_sign = ft_strchr(data->env, '=');
	if (data->eq_sign == NULL)
		return (NULL);
	data->key_len = data->eq_sign - data->env + 1;
	data->key = ft_strndup(data->env, data->key_len);
	if (!data->key)
		perror_exit("malloc err");
	data->value = ft_strdup(data->eq_sign + 1);
	if (!data->value)
		perror_exit("malloc err");
	return (create_node(data->key, data->value));
}

t_env	**create_link_list(char **envp, t_data *data)
{
	t_env	**head;
	t_env	*current;

	head = NULL;
	current = NULL;
	data->i = 0;
	while (envp[++data->i] != NULL)
	{
		data->new_node = create_node_from_env(envp[data->i], data);
		if (data->new_node != NULL)
		{
			if (head == NULL)
			{
				head = ft_calloc(1, sizeof(t_env *));
				*head = data->new_node;
				current = data->new_node;
			}
			else
			{
				current->next = data->new_node;
				current = data->new_node;
			}
		}
	}
	return (head);
}
