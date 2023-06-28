/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_export.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ssemanco <ssemanco@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 15:38:07 by ssemanco      #+#    #+#                 */
/*   Updated: 2023/06/28 12:36:07 by ssemanco      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void cmd_export(t_env **head, char *str)
{
    t_env* newNode = (t_env*)malloc(sizeof(t_env));
    char* equalSign = ft_strchr(str, '=');
    size_t keyLength = equalSign - str;
    newNode->key = ft_substr(str, 0, keyLength);;
    newNode->value = ft_strdup(equalSign);
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        t_env* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode; }
        printf("%s%s\n", newNode->key, newNode->value);
}