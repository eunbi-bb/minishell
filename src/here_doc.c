#include "../includes/minishell.h"
#include <stdio.h>
#include <fcntl.h>

int	create_heredoc(t_tokens *heredoc, bool quotes, char *tmp_file)
{
	int		fd;
	char	*str;

	fd = open(tmp_file, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
	str = readline(">"); 
	while (str && ft_strncmp(heredoc->data, str, ft_strlen(heredoc->data)))
	{
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
		str = readline(">");
	}
	free(str);
	close(fd);
	return(EXIT_SUCCESS);
}

char	tmp_filename(void)
{
	static int	i;
	char		*num;
	char		*filename;

	num = ft_itoa(i++);
	filename = ft_strjoin("tmp_", num);
	free(num);
	return (filename);
}

int	here_document(t_parser_utils *parser, t_cmd *heredoc, char *filename)
{
	g_global.begin = 1;
	g_global.finish = 0;
	bool	quotes;
	int		str;
	int		len;

	len = ft_strlen(heredoc->data);
	str = EXIT_SUCCESS;
	if ((heredoc->data[0] == '\'' && heredoc->data[len - 1] == '\'') || (heredoc->str[0] == '\"' && heredoc->data[len - 1] == '\"'))
		quotes = TRUE;
	else
		quotes = FALSE;
	str = create_heredoc(heredoc, quotes);
	parser->heredoc = TRUE;
	return (str);
}

int	send_heredoc(t_cmd	*cmd, t_parser_utils *parser)
{
	t_tokens	*start;
	int			s;

	start = cmd->redir;
	s = EXIT_SUCCESS;
	while (cmd->redir)
	{
		if (cmd->redir->redir_type == HERE_DOC)
		{
			if (cmd->redir->file_name)
				free(cmd->redir->file_name);
			cmd->redir->file_name = heredoc_filename();
			s = here_document(parser, cmd, cmd->redir->file_name);
			if (s)
			{
				g_global.error_num = 1;
				return (reset_parser(parser));
			}
		}
		cmd->redir = cmd->redir->next;
	}
	cmd->redir = start;
	return (EXIT_SUCCESS)
}