/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_export.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ssemanco <ssemanco@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 15:38:07 by ssemanco      #+#    #+#                 */
/*   Updated: 2023/09/23 18:13:46 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int var_exist(char *key, t_env *env)
{
    size_t len;

    len = ft_strlen(key);
    while (env)
    {
        if(ft_strncmp(key, env->key, len) == 0)
            return(0);
        env = env->next;
    }
    return (1);
}

void unset_var(t_env** head,char* key) {
    t_env* current;
    t_env* previous;

    current = *head;
    previous = NULL;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            if (previous == NULL) {
                *head = current->next;
            } else {
                previous->next = current->next;
            }
            free(current->key);
            free(current->value);
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

void cmd_export(t_env **head, char *str)
{
    t_env* newNode;
    char* equalSign;
    size_t keyLength;
    t_env* current;

    newNode = (t_env*)malloc(sizeof(t_env));
    equalSign = ft_strchr(str, '=');
    keyLength = equalSign - str + 1;
    newNode->key = ft_substr(str, 0, keyLength);
    if(var_exist(newNode->key, *head) == 0)
        unset_var(head, newNode->key);
    newNode->value = ft_strdup(equalSign + 1);
    newNode->next = NULL;
    if (*head == NULL) {
        *head = newNode;
    } else {
        current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode; }
        //printf("%s%s\n", newNode->key, newNode->value);
}