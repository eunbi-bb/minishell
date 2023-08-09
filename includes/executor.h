#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <fcntl.h>
# include "minishell.h"

typedef struct s_env
{
    char* key;
    char* value;
    struct s_env *next;
}               t_env;


int	executor(t_parser_utils *cmd, t_lexer_utils *lexer);
#endif