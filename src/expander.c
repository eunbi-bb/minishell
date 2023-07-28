#include "../includes/minishell.h"

// #include <stdlib.h>
// #include <sys/types.h>
// #include <sys/wait.h>
// #include <unistd.h>
// #include <stdio.h>

// int	expander(const char *command)
// {
// 	pid_t	pid;
// 	int		status;

// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("fork");
// 		exit(EXIT_FAILURE);
// 	}
// 	else if (pid == 0)
// 	{
// 		char*argv[] = {"sh", "-c", (char *)command, NULL};
// 		execve("/bin/sh", argv, NULL);
// 		perror("execve");
// 		exit(EXIT_FAILURE);
// 	}
// 	else
// 	{
// 		waitpid(pid, &status, 0);
// 		if (WIFEXITED(status))
// 			return WEXITSTATUS(status);
// 		else
// 		{
// 			fprintf(stderr, "Child process terminated abnormally.\n");
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	return (EXIT_SUCCESS);
// }

char	*check_expander(t_tokens *lexer, char *str)
{

}
