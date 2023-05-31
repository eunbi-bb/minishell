/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_pwd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ssemanco <ssemanco@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 15:35:55 by ssemanco      #+#    #+#                 */
/*   Updated: 2023/05/29 17:39:24 by ssemanco      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "exec.h"

Node* createNode(char* key, char* value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("malloc");
        exit(1);
    }
    newNode->key = strdup(key);
    newNode->value = strdup(value);
    newNode->next = NULL;
    printf("%s%s\n", newNode->key, newNode->value);
  
    return newNode;
}

Node* createLinkedList(char** envp) {
    Node* head = NULL;
    Node* current = NULL;

    for (int i = 0; envp[i] != NULL; i++) {
        char* env = envp[i];
        char* equalSign = strchr(env, '=');
        if (equalSign == NULL) {
            // Skip environment variables without an equal sign
            continue;
        }
        size_t keyLength = equalSign - env;
        char* key = strndup(env, keyLength);
        char* value = strdup(equalSign);

        Node* newNode = createNode(key, value);

        if (head == NULL) {
            head = newNode;
            current = newNode;
        } else {
            current->next = newNode;
            current = newNode;
        }
    }

    return head;
}


void cmd_pwd()
{
    char pwd[4500];

    if (getcwd(pwd, sizeof(pwd)) == NULL)
    {
        perror("getcwd");
        exit(-1);
    }
    else
        printf("%s\n", pwd);
}

int main(int argc, char **argv, char **envp)
{
    //int i = 0;
    
    argc = 0;
    argv = NULL;
    createLinkedList(envp);
    // while (envp[i])
    // {
    //      printf("%s\n", envp[i]);
    //      i++;
    // }
    //cmd_pwd();
    return (0);
}