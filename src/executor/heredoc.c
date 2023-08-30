#include "../includes/minishell.h"
#include "../includes/lexer.h"
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

int	create_heredoc(char *delim, char *filename)
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
	free(str);
	return (fd);
}

// int	create_heredoc_pipe(char *delim)
// {
// 	int		pipefd[2];
// 	char	*str;

// 	pipe(pipefd);
// 	while (1)
// 	{
// 		str = readline("> ");
// 		if (!ft_strncmp(delim, str, ft_strlen(delim)))
// 			break ;
// 		write(pipefd[1], str, ft_strlen(str));
// 		write(pipefd[1], "\n", 1);
// 		free(str);
// 	}
// 	free(str);
// 	close(pipefd[1]);
// 	return (pipefd);
// }

// void	multiple_heredocs(int *pipefd, t_redir *redir)
// {
// 	t_redir *tmp;
// 	char	buf[1024];
// 	ssize_t	byte;
// 	int		new_fd[2];

// 	if (tmp->next->redir_type == HERE_DOC)
// 	{
// 		tmp = tmp->next;
// 		create_heredoc_pipe(tmp->file_name);
// 		while ((byte = read(pipefd[0], buf, sizeof(buf))) > 0)
// 		{
// 			write(pipefd[1], buf, byte);
// 		}
// 		close(pipefd[1]);
// 	}

// }

void	here_document(t_cmd	*cmd, t_lexer_utils *lexer)
{
	static int	i;
	// int			fd;
	// int			*pipefd;
	char		*delim;
	t_redir		*start;

	start = cmd->redir;
	while (cmd->redir)
	{
		if (cmd->redir->redir_type == HERE_DOC && cmd->redir)
		{
			delim = cmd->redir->file_name;
			cmd->redir->file_name = tmp_filename(i);
			lexer->heredoc_filename = ft_strdup(cmd->redir->file_name);
			i++;
			// if (cmd->redir->next->redir_type == HERE_DOC)
			// 	pipefd = create_heredoc_pipe(delim);
			// else
			// {
			// 	pipefd = 0;
			create_heredoc(delim, cmd->redir->file_name);
			// }
			// if (pipefd != 0)
			// 	multiple_heredocs(&pipefd, cmd->redir);
		}
		cmd->redir = cmd->redir->next;
	}
	cmd->redir = start;
}
