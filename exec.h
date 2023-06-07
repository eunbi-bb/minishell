#ifndef EXEC_H
# define EXEC_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "libft/libft.h"

typedef struct Node {
    char* key;
    char* value;
    struct Node* next;
} Node;

Node* createLinkedList(char** envp);
int cmd_echo(int argc, char **argv);
void cmd_cd(int argc, char **path);
void cmd_pwd();

#endif