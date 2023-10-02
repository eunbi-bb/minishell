#include "minishell.h"
#include "error.h"
#include <fcntl.h>

int	open_infile(char *file, t_cmd *cmd)
{
	int	fd;

	fd = open(file, O_RDONLY); 
	if (fd == -1)
		err_msg(ERROR_INFILE);
	dup2(fd, STDIN_FILENO);
	if (cmd->redir->redir_type == HERE_DOC)
		unlink(file);
	close(fd);
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
	t_redir	*head;
	int		fd_in;

	head = cmd->redir;
	while (cmd->redir != NULL)
	{
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
	cmd->redir = head;
	return (fd_in);
}
