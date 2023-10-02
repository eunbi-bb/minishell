/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 16:13:53 by eucho         #+#    #+#                 */
/*   Updated: 2023/10/02 16:13:55 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

char	*tmp_filename(int i)
{
	char		*num;
	char		*filename;

	num = ft_itoa(i);
	filename = ft_strjoin("obj/.tmp_", num);
	free(num);
	return (filename);
}

void	create_heredoc(char *delim, char *filename)
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
		if (!ft_strncmp(delim, str, ft_strlen(delim)))
			break ;
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
	}
	free(delim);
	free(str);
}

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
