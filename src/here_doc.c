#inlcude "../includes/minishell.h"

int	create_heredoc(t_tokens *heredoc, bool quotes)
{
	int		fd;
	char	*str;

	fd = open("", O_TMPFILE | O_RDWR, S_IRUSR | S_IWUSR);
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

char	make_heredoc_filename(void)
{
	sts
}

int	here_document(parser_utils *parser, t_tokens *heredoc, char *file_name)
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