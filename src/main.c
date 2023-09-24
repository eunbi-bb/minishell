#include "minishell.h"
#include "executor.h"
#include "error.h"
#include <readline/readline.h>
#include <readline/history.h>

int sigint_received;

void	init_utils(t_lexer_utils *lexer, t_parser_utils	*parser)
{
	lexer->pipe_num = 0;
	lexer->heredoc = false;
	lexer->token_list = NULL;
	parser->cmd_list = NULL;
	parser->pid = 0;
	parser->reset = false;
	parser->env = NULL;
}

int	shell_loop(t_lexer_utils *lexer, t_parser_utils	*parser_utils)
{
	char			*line;
	int				status;

	status = 0;
	rl_catch_signals = 0;
	if (signal(SIGINT, sigint_handler) == SIG_ERR) {
        perror("signal");
        exit(EXIT_FAILURE);
    }
	signal(SIGQUIT, SIG_IGN);
	while (status == 0)
	{
		if (sigint_received)
            sigint_received = 0; // Reset the flag
		line = readline("Minishell% ");
		lexer->arg = ft_strtrim(line, " ");
		if (lexer->arg == NULL || ft_strncmp(lexer->arg, "exit", 4) == 0)
		{
			free(line);
			write(STDOUT_FILENO, "exit\n", 6);
			exit(EXIT_SUCCESS);
		}
		if (*line)
            add_history(line);
		// if (lexer->arg[0] == '\0')
		// 	return(reset_utils(lexer, parser_utils));
		// if (match_quotes(lexer->arg) == false)
		// 	return (err_msg(ERROR_QUOTE));
		if (lexical_analyzer(lexer) == false)
			return (err_msg(ERROR_LEXER));
		parser(lexer, parser_utils);
		// int n = 1;

		// while (parser_utils->cmd_list)
		// {
		// 	printf("\n--------Number of command : %d---------\n", n);
		// 	int	arg_num = count_args(lexer->token_list);
		// 	int i = 0;
		// 	if (parser_utils->cmd_list->data && parser_utils->cmd_list->data[i] != NULL)
		// 	{
		// 		while (parser_utils->cmd_list->data[i] && i <= arg_num)
		// 		{
		// 			printf("cmd->data[%d] : %s\n", i,parser_utils->cmd_list->data[i]);
		// 			i++;
		// 		}
		// 	}
		// 	if (parser_utils->cmd_list->redir)
		// 	{
		// 		t_redir *cmd_redir = parser_utils->cmd_list->redir;
		// 		while (cmd_redir)
		// 		{
		// 			printf("cmd->redir_type : %d\n", cmd_redir->redir_type);
		// 			printf("cmd->filename : %s\n\n", cmd_redir->file_name);
		// 			cmd_redir = cmd_redir->next;
		// 		}
		// 	}
		// 	parser_utils->cmd_list = parser_utils->cmd_list->next;
		// 	n++;
		// }
		status = executor(parser_utils, lexer);
		free(line);
		destroy_lexer_list(&lexer->token_list);
		destroy_parser_list(&parser_utils->cmd_list);
		lexer->pipe_num = 0;
		if (sigint_received == 2)
			exit(0) ;
	}
	return (status);
}


int	main(int argc, char **argv, char **envp)
{
	t_lexer_utils	lexer;
	t_parser_utils	parser;
	int				exit_code;

	//system ("leaks minishell -q");
	argv = NULL;
	if (argc != 1 && argv[0] != NULL)
	{
		printf("Invalid argument.\n");
		exit(0);
	}
	rl_initialize();
	init_utils(&lexer, &parser);
	parser.env = createLinkedList(envp);
	printf("%s%s\n", (*parser.env)->key, (*parser.env)->value);
	parser.cmd_dirs = get_cmd_dirs(parser.env);
	//pwd(&parser);status
	exit_code = shell_loop(&lexer, &parser);
	if (sigint_received == 2)
		exit(0);
	printf("exit code : %d\n", exit_code);
	destroy_env_list(parser.env);
	destroy_lexer_list(&lexer.token_list);
	destroy_parser_list(&parser.cmd_list);
	return (exit_code);
}