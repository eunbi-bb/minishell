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
# include "lexer.h"

char	*command_check(char **path, char *cmd);
void	create_pipes(int pipe_num, int fds[]);
void	close_ends(int pipe_num, int fds[]);
int	wait_pipes(pid_t pid, int pipe_num);
#endif