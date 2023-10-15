/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 16:14:16 by eucho         #+#    #+#                 */
/*   Updated: 2023/10/15 21:03:19 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "error.h"
#include <fcntl.h>

int	open_infile(char *file, t_redir *redir)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		err_msg(ERROR_INFILE);
	dup2(fd, STDIN_FILENO);
	if (redir->redir_type == HERE_DOC)
		unlink(file);
	close(fd);
	return (fd);
}

int	create_outfile(t_redir *redir)
{
	int	fd;
	int	type;

	if (redir->redir_type == APPEND)
		type = O_APPEND;
	else
		type = O_TRUNC;
	fd = open(redir->file_name, O_CREAT | O_RDWR | type, 0000644);
	if (fd == -1)
		err_msg(ERROR_OUTFILE);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (EXIT_SUCCESS);
}

int	redirection(t_redir *redir)
{
	t_redir	*head;
	int		fd_in;

	head = redir;
	while (redir != NULL)
	{
		if (redir->redir_type == GREATER || redir->redir_type == APPEND)
		{
			if (create_outfile(redir))
				return (EXIT_FAILURE);
		}
		if (redir->redir_type == LESSER || redir->redir_type == HERE_DOC)
		{
			fd_in = open_infile(redir->file_name, redir);
			if (fd_in == -1)
				return (EXIT_FAILURE);
		}
		redir = redir->next;
	}
	redir = head;
	return (fd_in);
}
