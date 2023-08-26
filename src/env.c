/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ssemanco <ssemanco@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/31 14:20:34 by ssemanco      #+#    #+#                 */
/*   Updated: 2023/08/24 15:55:10 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
			head = (t_env**)malloc(sizeof(t_env*));
            *head = newNode;
            current = newNode;
        } else {
            current->next = newNode;
            current = newNode;
        }
    }

    return head;
}

