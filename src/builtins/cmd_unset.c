/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_unset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ssemanco <ssemanco@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 14:32:33 by ssemanco      #+#    #+#                 */
/*   Updated: 2023/09/17 13:02:26 by ssemanco      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void cmd_unset(t_env** head,char* key) {
    t_env* current = *head;
    t_env* previous = NULL;

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