/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_export.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ssemanco <ssemanco@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 15:38:07 by ssemanco      #+#    #+#                 */
/*   Updated: 2023/06/21 17:56:19 by ssemanco      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void cmd_export(t_env **head, char *var, char *val)
{
    t_env* newNode = (t_env*)malloc(sizeof(t_env));
    newNode->key = strdup(var);
    newNode->value = strdup(val);
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        t_env* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode; }
}