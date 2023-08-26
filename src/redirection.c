#include "../includes/minishell.h"
#include "../includes/error.h"
#include <fcntl.h>

int	open_infile(char *file, t_cmd *cmd)
{
	int	fd;

	fd = open(file, O_RDONLY); 
	dup2(fd, STDIN_FILENO);
	if (cmd->redir->redir_type == HERE_DOC)
		unlink(file);
	close(fd);
	// if (fd == -1)
	// 	err_msg(ERROR_INFILE);
	// if (fd == -1 && dup2(fd, STDIN_FILENO) == -1)
	// 	err_msg(ERROR_PIPE_IN);
	// else
	// 	close(fd);
	return (fd);
}

int	create_outfile(t_cmd *cmd)
{
	int	fd;

	if (cmd->redir->redir_type == APPEND)
	{
		fd = open(cmd->redir->file_name, O_CREAT | O_RDWR | O_APPEND, 0000644);
		if (fd == -1)
			err_msg(ERROR_OUTFILE);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else
	{
		fd = open(cmd->redir->file_name, O_CREAT | O_RDWR | O_TRUNC, 0000644);
		if (fd == -1)
			err_msg(ERROR_OUTFILE);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (EXIT_SUCCESS);
}

int	redirection(t_cmd *cmd)
{
	t_redir	*tmp;
	int		fd_in;

	tmp = cmd->redir;
	while (cmd->redir != NULL)
	{
		//printf("%d\n", cmd->redir->redir_type);
		if (cmd->redir->redir_type == GREATER || cmd->redir->redir_type == APPEND)
		{
			if (create_outfile(cmd))
				return (EXIT_FAILURE);
		}
		else if (cmd->redir->redir_type == LESSER || cmd->redir->redir_type == HERE_DOC)
		{
			fd_in = open_infile(cmd->redir->file_name, cmd);
			if (fd_in == -1)
				return (EXIT_FAILURE);
		}
		cmd->redir = cmd->redir->next;
	}
	cmd->redir = tmp;
	return (fd_in);
}
