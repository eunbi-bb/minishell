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

#include "../includes/minishell.h"

void cmd_export(t_env **head, char *str)
{
	printf("GOT HERE\n");
    t_env* newNode = (t_env*)malloc(sizeof(t_env));
	printf("here\n");
    char* equalSign = ft_strchr(str, '=');
    size_t keyLength = equalSign - str;
	printf("hi\n");
    newNode->key = ft_substr(str, 0, keyLength);;
    newNode->value = ft_strdup(equalSign + 1);
    newNode->next = NULL;
	printf("GOT HERE lol\n");
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