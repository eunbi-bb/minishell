/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_unset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ssemanco <ssemanco@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 14:32:33 by ssemanco      #+#    #+#                 */
/*   Updated: 2023/10/11 23:10:13 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int cmd_unset(t_env** head,char* key) {
    t_env* current = *head;
    t_env* previous = NULL;
    char *key_eq;

    if (!key)
        return (0);
    while (current != NULL) {
        key_eq = ft_strjoin(key, "=");
		// if (!key_eq)
		// 	err_msg("malloc fail");
        if (strcmp(current->key, key_eq) == 0) {
            if (previous == NULL) {
                *head = current->next;
            } else {
                previous->next = current->next;
            }
            free(current->key);
            free(current->value);
            free(current);
            free(key_eq);
            return (0);
        }
        previous = current;
        current = current->next;
    }
	return (0);
}