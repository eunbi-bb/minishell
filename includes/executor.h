#ifndef EXECUTOR_H
# define EXECUTOR_H

#include <sys/types.h>
#include "minishell.h"

typedef	struct	s_pipe
{
	pid_t	*pid;
	int		pipes;
	bool	reset;
}	t_pipe;

#endif