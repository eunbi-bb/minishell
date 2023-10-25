/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ssemanco <ssemanco@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/31 14:20:34 by ssemanco      #+#    #+#                 */
/*   Updated: 2023/10/24 22:13:46 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "error.h"

// char	**free_array(char **str, int count)
// {
// 	int	i;

// 	i = 0;
// 	while (i < count)
// 	{
// 		free(str[i]);
// 		i++;
// 	}
// 	free(str);
// 	return (NULL);
// }

// int	count_env_llist(t_env **head)
// {
// 	int	i;
// 	t_env	*current;

// 	i = 0;
// 	current = *head;
//     while (current)
//     {
//         i++;
//         current = current->next;
//     }
// 	return (i + 1);
// }

// char	**join_key_value(t_env **head)
// {
// 	char	**str;
// 	int		i;
// 	t_env	*current;

// 	str = (char **)ft_calloc(count_env_llist(head), sizeof(char *));
// 	current = *head;
// 	i = 0;
// 	while (current)
// 	{
// 		str[i] = ft_strjoin(current->key, current->value);
// 		if (!str[i])
// 			return (free_array(str, i + 1));
// 		i++;
// 		current = current->next;
// 	}
// 	str[i] = NULL;
// 	return (str);
// }


t_env	*create_env_node(char* key, char* value)
{
    t_env* new_node;
	
	new_node = ft_calloc(1, sizeof(t_env));
    if (new_node == NULL) 
		perror_exit("malloc err");
    new_node->key = ft_strdup(key);
	free(key);
    new_node->value = ft_strdup(value);
	free(value);
    new_node->next = NULL;
    return (new_node);
}

void	add_after_env(t_env **before, t_env *new_node)
{
	t_env	*head;

	head = *before;
	if (head == NULL)
	{
		*before = new_node;
	}
	else
	{
		while (head->next != NULL)
			head = head->next;
		head->next = new_node;
	}
}

int cmd_env(t_env *env)
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


void	create_env_list(t_parser *parser, char** envp)
{
	char	*env;
	char	*equal_sign;
	char	*key;
	char	*value;
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		env = ft_strdup(envp[i]);
		equal_sign = ft_strchr(env, '=');
		if (equal_sign == NULL)
			return ;
		key = ft_strndup(env, equal_sign - env + 1);
		if (!key)
			perror_exit("malloc err");
		value = ft_strdup(equal_sign + 1);
		if	(!value)
			perror_exit("malloc err");
		free(env);
		add_after_env(&parser->env, create_env_node(key, value));
		i++;
	}
}