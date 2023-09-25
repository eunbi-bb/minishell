#include "minishell.h"
#include "lexer.h"
#include <stdio.h>
#include <fcntl.h>

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

	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0000777);
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
	return(fd);
}

int	here_document(t_cmd	*cmd, t_lexer_utils *lexer)
{
	static int	i;
	int			fd;
	char		*delim;
	t_redir		*start;
	start = cmd->redir;

	(void)lexer;
	while (cmd->redir)
	{
		if (lexer->heredoc == true && cmd->redir)
		{
			delim = cmd->redir->file_name;
			cmd->redir->file_name = tmp_filename(i);
			// lexer->heredoc_filename = ft_strdup(cmd->redir->file_name);
			// printf("%s\n", lexer->heredoc_filename);
			i++;
			fd = create_heredoc(delim, cmd->redir->file_name);
		}
		cmd->redir = cmd->redir->next;
	}
	cmd->redir = start;
	return (fd);
}
