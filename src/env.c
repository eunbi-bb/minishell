/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ssemanco <ssemanco@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/31 14:20:34 by ssemanco      #+#    #+#                 */
/*   Updated: 2023/09/05 13:36:31 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**free_array(char **str, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free((void *)str[i]);
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
	const char	*key_is;
	int		i;
	t_env	*current;

	str = (char **)ft_calloc(count_env_llist(head), sizeof(char *));
	current = *head;
	i = 0;
	while (current)
	{
		key_is = ft_strjoin((char *)current->key, "=");
		if (!key_is)
			return (free_array(str, i));
		str[i] = ft_strjoin(key_is, (char *)current->value);
		if (!str[i])
			return (free_array(str, i + 1));
		i++;
		current = current->next;
		free((void *)key_is);
	}
	str[i] = NULL;
	return str;
}

t_env* createNode(char* key, char* value) {
    t_env* newNode = ft_calloc(1, sizeof(t_env));
    if (newNode == NULL) {
        perror("malloc");
        exit(1);
    }
    newNode->key = strdup(key);
    newNode->value = strdup(value);
    newNode->next = NULL;
    //printf("%s%s\n", newNode->key, newNode->value);
  
    return newNode;
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
        size_t keyLength = equalSign - env;
        char* key = strndup(env, keyLength);
        char* value = strdup(equalSign + 1);

        t_env* newNode = createNode(key, value);

        if (head == NULL) {
			// head = (t_env**)malloc(sizeof(t_env*));
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
