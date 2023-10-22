/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 16:13:53 by eucho         #+#    #+#                 */
/*   Updated: 2023/10/19 23:02:18 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

static char	*tmp_filename(int i)
{
	char		*num;
	char		*filename;

	num = ft_itoa(i);
	filename = ft_strjoin("obj/.tmp_", num);
	free(num);
	return (filename);
}

/*
*	Create a temporary file to store the written inputs using 'write()'
*	until a line containing the delimiter is encountered.
*/
static void	create_heredoc(char *delim, char *filename)
{
	int		fd;
	char	*str;

	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0000644);
	if (fd < 0)
	{
		unlink(filename);
		perror("heredoc error\n");
	}
	while (1)
	{
		str = readline("> ");
		if (str == NULL)
			break ;
		if (!ft_strncmp(delim, str, ft_strlen(delim)))
			break ;
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		if (str)
			free(str);
	}
	free(delim);
	if (str)
		free(str);
}

/*
*	If the redirecion type is HERE_DOC('<<'),
*	the 'cmd->redir->file_name' will serve as a delimiter and
*	be replaced with a temporary filename to store the written inputs.
*/
void	here_document(t_cmd	*cmd)
{
	static int	i;
	char		*delim;
	t_redir		*head;

	head = cmd->redir;
	while (cmd->redir)
	{
		if (cmd->redir->redir_type == HERE_DOC && cmd->redir)
		{
			delim = cmd->redir->file_name;
			cmd->redir->file_name = tmp_filename(i);
			i++;
			create_heredoc(delim, cmd->redir->file_name);
		}
		cmd->redir = cmd->redir->next;
	}
	cmd->redir = head;
}
