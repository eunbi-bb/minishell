/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 16:14:16 by eucho         #+#    #+#                 */
/*   Updated: 2023/10/24 16:06:02 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "error.h"
#include <fcntl.h>

static int	open_infile(char *file, t_redir *redir)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		err_msg(ERROR_INFILE);
	dup2(fd, STDIN_FILENO);
	if (redir->redir_type == HERE_DOC && !redir->next)
		unlink(file);
	if (fd > 0)
		close(fd);
	return (fd);
}

static int	create_outfile(t_redir *redir)
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
	if (fd > 0)
		close(fd);
	return (EXIT_SUCCESS);
}

/*
*	Depending on the redirection type, 
*	it either executes 'create_outfile()' or 'open_infile()'.
*/
static int	redirection(t_redir *redir)
{
	t_redir	*head;
	int		fd_in;

	head = redir;
	fd_in = 0;
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

void	unlink_exit(char *file_name)
{
	unlink(file_name);
	exit(EXIT_SUCCESS);
}

/*
*	If the redirection type is HERE_DOC, start by executing here_document() 
*	to generate a temporary file. If Heredoc is executed without any other command,
*	then unlink the temporary file and exit. 
*	Otherwise, proceed to execute redirection(). The redirection() returns 'fd_in' 
*	if the infile has been opened. In the child_process(), it will be closed.
*/
int	execute_redir(t_parser *parser, t_redir *redir, int fd_in)
{
	t_redir	*head;

	head = redir;

	while (redir)
	{
		if (redir != NULL && redir->redir_type == HERE_DOC)
		{
			here_document(parser->cmd_list);
			if (!parser->cmd_list->data && !redir->next)
				unlink_exit(redir->file_name);
		}
		if (redir != NULL && redir->redir_type != DEFAULT)
			fd_in = redirection(parser->cmd_list->redir);
		redir = redir->next;
	}
	redir = head;
	return (fd_in);
}
