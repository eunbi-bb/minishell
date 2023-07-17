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
	int		file;
	char	*str;

	file = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (file < 0)
		return(2);
	while (1)
	{
		str = readline("> ");
		if (!ft_strncmp(delim, str, ft_strlen(delim)))
			break ;
		write(file, str, ft_strlen(str));
		write(file, "\n", 1);
		free(str);
	}
	free(str);
	close(file);
	return(1);
}

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
