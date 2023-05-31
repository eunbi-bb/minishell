#ifndef EXEC_H
# define EXEC_H

typedef struct Node {
    char* key;
    char* value;
    struct Node* next;
} Node;

#endif