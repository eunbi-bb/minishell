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
#include "error.h"

// Function to split the linked list into two halves
void splitList(t_env *source, t_env **leftRef, t_env **rightRef) {
    t_env *fast;
    t_env *slow;

    if (source == NULL || source->next == NULL) {
        *leftRef = source;
        *rightRef = NULL;
    } else {
        slow = source;
        fast = source->next;

        while (fast != NULL) {
            fast = fast->next;
            if (fast != NULL) {
                slow = slow->next;
                fast = fast->next;
            }
        }

        *leftRef = source;
        *rightRef = slow->next;
        slow->next = NULL;
    }
}


t_env* merge(t_env *left, t_env *right) {
    t_env *result = NULL;

    if (left == NULL)
        return right;
    if (right == NULL)
        return left;

    if (strcmp(left->key, right->key) <= 0) {
        result = left;
        result->next = merge(left->next, right);
    } else {
        result = right;
        result->next = merge(left, right->next);
    }

    return result;
}

// Merge Sort function for sorting the linked list
t_env* mergeSort(t_env *head) {
    if (head == NULL || head->next == NULL)
        return head;

    t_env *left;
    t_env *right;
    t_env *sorted;

    splitList(head, &left, &right);

    left = mergeSort(left);
    right = mergeSort(right);

    sorted = merge(left, right);

    return sorted;
}

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

void printList(t_env *head) {
    t_env *current = head;
    while (current != NULL) {
        printf("declare -x %s %s\n", current->key, current->value);
        current = current->next;
    }
}

t_env* insert_node(char *str, t_env **head)
{
    char* equalSign;
    size_t keyLength;
    t_env* newNode;
    t_env* current;

    current = *head;
    newNode = (t_env*)malloc(sizeof(t_env));
    if (newNode == NULL) {
        perror("malloc");
        exit(1);
    }
    equalSign = ft_strchr(str, '=');
    if (equalSign == NULL)
        return (NULL);
    keyLength = equalSign - str + 1;
    newNode->key = ft_substr(str, 0, keyLength);
    if(var_exist(newNode->key, current) == 0)
        unset_var(head, newNode->key);
    newNode->value = ft_strdup(equalSign + 1);
    newNode->next = NULL;
    return(newNode);
}

int valid_char(char *str)
{
    if (ft_isdigit(str[0]))
        return(1);;
    if (ft_strchr(str, '-'))
       return(1);;
    return(0);
}

int cmd_export(t_env **head, char **str)
{
    t_env* newNode;
    t_env* current;
	t_env* sorted;
    int     i;

    i = 1;
	if (!str[1])
	{
		sorted = mergeSort(*head);
		printList(sorted);
	} else {
            while (str[i])
    {
        if (valid_char(str[i]) == 1)
        {
            printf("export: '%s': not a valid identifier\n", str[i]);
            return (1);
        }
        newNode = insert_node(str[i], head);
        if (*head == NULL) {
            *head = newNode;
        } else {
            current = *head;
            while (current->next != NULL) {
                current = current->next;
        }
        current->next = newNode; }
        i++;
    }
    }
    return(0);
}