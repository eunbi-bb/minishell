#include "../includes/minishell.h"
#include "../includes/error.h"

void	init_utils(t_lexer_utils *lexer, t_parser_utils	*parser)
{
	lexer->pipe_num = 0;
	lexer->heredoc = FALSE;
	lexer->token_list = NULL;
	parser->cmd_list = NULL;
	parser->pid = 0;
	parser->reset = FALSE;
	parser->env = NULL;
	printf("LOL\n");
}

int	shell_loop(t_lexer_utils *lexer, t_parser_utils	*parser_utils)
{
	char			*line;
	int				status;

	status = 1;
	while (status)
	{
		line = readline("Minishell% ");
		lexer->arg = ft_strtrim(line, " ");
		if (lexer->arg == NULL)
		{
			write(STDOUT_FILENO, "exit", 5);
			exit(EXIT_SUCCESS);
		}
		// if (lexer->arg[0] == '\0')
		// 	return(reset_utils(lexer, parser_utils));
		if (match_quotes(lexer->arg) == FALSE)
			return (err_msg(ERROR_QUOTE));
		if (lexical_analyzer(lexer) == FALSE)
			return (err_msg(ERROR_LEXER));
		parser(lexer, parser_utils);
		if (lexer->heredoc == TRUE)
			here_document(parser_utils->cmd_list, lexer);
		//status = executor(parser_utils, lexer);
		free(line);
		free(lexer->token_list);
		free(parser_utils->cmd_list);
	}
	return (g_global.exit_stat);
}


int	main(int argc, char **argv, char **envp)
{
	t_lexer_utils	lexer;
	t_parser_utils	parser;

	argv = NULL;
	if (argc != 1)
	{
		printf("Invalid argument.\n");
		exit(0);
	}

	init_utils(&lexer, &parser);
	parser.env = createLinkedList(envp);
	get_cmd_dirs(parser.env);
	//pwd(&parser);
	shell_loop(&lexer, &parser);
	return (g_global.exit_stat);
}