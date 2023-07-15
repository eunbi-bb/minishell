#include "./includes/minishell.h"
#include <stdio.h>
#include <fcntl.h>

char	tmp_filename(int i)
{
	char		*num;
	char		*filename;

	num = ft_itoa(i);
	filename = ft_strjoin("tmp_", num);
	free(num);
	return (filename);
}

int	here_document(char	*delim, char *filename)
{
	int		heredoc;
	int		file;
	char	*str;

	file = open(tmp_file, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
	if (file < 0)
		return(2);
	while (1)
	{
		str = readline(">");
		if (!ft_strncmp(delim, str, ft_strlen(delim)))
			break ;
		write(file, str, ft_strlen(str));
		write(file, "\n", 1);
		free(str);
	}
	free(str);
	close(file);
	return(EXIT_SUCCESS);
}

int	send_heredoc(t_cmd	*cmd, t_lexer_utils *lexer)
{
	static int	i;
	char		*delim;
	t_tokens	*start;

	start = cmd->redir;
	s = EXIT_SUCCESS;
	while (cmd->redir)
	{
		if (lexer->heredoc == TRUE)
		{
			delim = cmd->redir->file_name;
			cmd->redir->file_name = tmp_filename(i);
			i++;
			here_document(delim, cmd->redir->file_name);
		}
		cmd->redir = cmd->redir->next;
	}
	cmd->redir = start;
	return (EXIT_SUCCESS)
}