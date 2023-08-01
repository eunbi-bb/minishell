#ifndef EXECUTOR_H
# define EXECUTOR_H

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "minishell.h"

typedef	struct	s_pipe
{
	pid_t	*pid;
	int		pipes;
	bool	reset;
}	t_pipe;

typedef struct s_env
{
    char* key;
    char* value;
    struct s_env *next;
}               t_env;

#endif