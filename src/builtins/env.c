/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ssemanco <ssemanco@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/31 14:20:34 by ssemanco      #+#    #+#                 */
/*   Updated: 2023/10/13 21:37:49 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**free_array(char **str, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

int	count_env_llist(t_env **head)
{
	int	i;
	t_env	*current;

	i = 0;
	current = *head;
    while (current)
    {
        i++;
        current = current->next;
    }
	return (i + 1);
}

char	**join_key_value(t_env **head)
{
	char	**str;
	int		i;
	t_env	*current;

	str = (char **)ft_calloc(count_env_llist(head), sizeof(char *));
	current = *head;
	i = 0;
	while (current)
	{
		str[i] = ft_strjoin(current->key, current->value);
		if (!str[i])
			return (free_array(str, i + 1));
		i++;
		current = current->next;
		// free((void *)key_is);
	}
	str[i] = NULL;
	return (str);
}


t_env* createNode(char* key, char* value) {
    t_env* newNode = ft_calloc(1, sizeof(t_env));
    if (newNode == NULL) {
        perror("malloc");
        exit(1);
    }
    newNode->key = strdup(key);
	free(key);
    newNode->value = strdup(value);
	free(value);
    newNode->next = NULL;
    return newNode;
}

int cmd_env(t_env *env)
{
    while(env)
    {
        printf("%s%s\n", env->key, env->value);
        env = env->next;
    }
    return (0);
}

t_env **createLinkedList(char** envp) {
    t_env** head = NULL;
    t_env* current = NULL;

    for (int i = 0; envp[i] != NULL; i++) {
        char* env = envp[i];
        char* equalSign = strchr(env, '=');
        if (equalSign == NULL) {
            // Skip environment variables without an equal sign
            continue;
        }
        size_t keyLength = equalSign - env + 1;
        char* key = strndup(env, keyLength);
        char* value = strdup(equalSign + 1);

        t_env* newNode = createNode(key, value);

        if (head == NULL) {
			head = ft_calloc(1, sizeof(t_env*));
            *head = newNode;
            current = newNode;
        } else {
            current->next = newNode;
            current = newNode;
        }
    }
    return head;
}
