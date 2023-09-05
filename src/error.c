#include <unistd.h>
#include "../includes/error.h"
#include "../includes/minishell.h"

void	cmd_error(char *cmd)
{
	write(STDERR_FILENO, "Minishell: ", 11);
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, ERROR_CMD"\n", ft_strlen(ERROR_CMD) + 1);
	exit(1);
}

int	err_msg(char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	return(EXIT_FAILURE);
}

void	perror_exit(char *str)
{
	perror(str);
	exit(errno);
}