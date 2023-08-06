#include "../includes/minishell.h"
#include "../includes/executor.h"
#include "../includes/error.h"

int	g_exit_stat;

int	init_utils(t_lexer_utils *lexer, t_parser_utils	*parser)
{
	lexer->pipe_num = 0;
	lexer->heredoc = FALSE;
	lexer->token_list = NULL;
	parser->cmd_list = NULL;
	parser->pid = NULL;
	parser->reset = FALSE;
	parser->env = NULL;
}


void	shell_loop(t_lexer_utils *lexer, t_parser_utils	*parser)
{
	char			*line;
	int				status;

	while (status)
	{
		line = readline("Minishell% ");
		lexer->arg = ft_strtrim(line, " ");
		if (lexer->arg == NULL)
		{
			write(STDOUT_FILENO, "exit", 5);
			exit(EXIT_SUCCESS);
		}
		if (lexer->arg[0] == NULL)
			return(reset_utils(lexer, parser));
		if (match_quotes(lexer->arg) == FALSE)
			return (err_msg(ERROR_QUOTE));
		if (lexical_analyzer(lexer) == FALSE);
			return (err_msg(ERROR_LEXER));
		parser(lexer, parser_list);
		if (lexer->heredoc == TRUE)
			here_document(parser->cmd_list, lexer);
		status = executer(parser->cmd_list);
		free(line);
		free(lexer->token_list);
		free(parser->cmd_list);
	}
}


int	main(int argc, char **argv, char **envp)
{
	t_lexer_utils	lexer;
	t_parser_utils	parser;

	if (argc != 1)
	{
		printf("Invalid argument.\n");
		exit(0);
	}

	init_utils(&lexer, &parser);
	parser.env = createLinkedList(envp);
	//pwd(&parser);
	//parser.envp = env(envp);
	shell_loop(&lexer, &parser);
	return (exit_stat);
}