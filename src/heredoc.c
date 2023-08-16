#include "../includes/minishell.h"
#include "../includes/lexer.h"
#include <stdio.h>
#include <fcntl.h>

char	*tmp_filename(int i)
{
	char		*num;
	char		*filename;

	num = ft_itoa(i);
	filename = ft_strjoin("tmp_", num);
	free(num);
	return (filename);
}

int	create_heredoc(char *delim, char *filename)
{
	int		fd;
	char	*str;

	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0000644);
	if (fd < 0)
		return(2);
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
	// dup2(fd, 0);
	// close(fd);
	return(fd);
}

// int	heredoc_redirection(t_lexer_utils *lexer, t_parser_utils *cmd, int fds[])
// {
// 	int	fd;

// 	if (lexer->heredoc == TRUE)
// 	{
// 		close(fds[0]);
// 		fd = open(cmd->cmd_list->redir->file_name, O_RDONLY);
// 	}
// 	else
// 		fd = fds[0];
// 	return (fd);
// }

int	here_document(t_cmd	*cmd, t_lexer_utils *lexer)
{
	static int	i;
	char		*delim;
	t_redir		*start;

	start = cmd->redir;
	while (cmd->redir)
	{
		if (lexer->heredoc == TRUE)
		{
			delim = cmd->redir->file_name;
			cmd->redir->file_name = tmp_filename(i);
			i++;
			create_heredoc(delim, cmd->redir->file_name);
		}
		cmd->redir = cmd->redir->next;
	}
	cmd->redir = start;
	return (1);
}
