#include "../includes/minishell.h"
#include "../includes/executor.h"
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
}

void	free_lexer_nodes(t_tokens *head)
{
	t_tokens *current;
	t_tokens *tmp;

	current = head;
	while (current != NULL)
	{
		tmp = current;
		current = current->next;
		free(tmp);
	}
}

void	destroy_lexer_list(t_tokens **head_ref)
{
	free_lexer_nodes(*head_ref);
	*head_ref = NULL;
}

void	free_parser_nodes(t_cmd *head)
{
	t_cmd *current;
	t_cmd *tmp;

	current = head;
	while (current != NULL)
	{
		tmp = current;
		current = current->next;
		free(tmp);
	}
}

void	destroy_parser_list(t_cmd **head_ref)
{
	free_parser_nodes(*head_ref);
	*head_ref = NULL;
}

int	shell_loop(t_lexer_utils *lexer, t_parser_utils	*parser_utils)
{
	char			*line;
	int				status;

	status = 0;
	while (status == 0)
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
		// if (lexer->heredoc == TRUE)
		// 	here_document(parser_utils->cmd_list, lexer);
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
	}
	return (status);
}


int	main(int argc, char **argv, char **envp)
{
	t_lexer_utils	lexer;
	t_parser_utils	parser;
	int				exit_code;

	argv = NULL;
	if (argc != 1 && argv[0] != NULL)
	{
		printf("Invalid argument.\n");
		exit(0);
	}
	init_utils(&lexer, &parser);
	parser.env = createLinkedList(envp);
	parser.cmd_dirs = get_cmd_dirs(parser.env);
	//pwd(&parser);status
	exit_code = shell_loop(&lexer, &parser);
	printf("exit code : %d\n", exit_code);
	// free (str);
	return (exit_code);
}