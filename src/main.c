/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 16:11:54 by eucho         #+#    #+#                 */
/*   Updated: 2023/10/10 16:15:02 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "error.h"

int	g_exit_status;

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

char	*readline_loop(void)
{
	char 	*line;

	rl_on_new_line();
	line = readline("Minishell% ");
	if (!line)
	{
		rl_clear_history();
		return (0);
	}
	if (!*line)
	{
		free(line);
		return (readline_loop());
	}
	if (*line)
		add_history(line);
	return (line);
}

void	shell_loop(t_lexer_utils *lexer, t_parser_utils	*parser_utils)
{
	char			*line;
	(void)parser_utils;
	g_exit_status = 0;
	// rl_catch_signals = 0;
	// if (signal(SIGINT, sigint_handler) == SIG_ERR)
	// 	perror_exit(ERROR_SIG);
	// signal(SIGQUIT, SIG_IGN);
	while (g_exit_status == 0)
	{
		// if (sigint_received)
        //     sigint_received = 0; // Reset the flag
		line = readline_loop();
		lexer->arg = ft_strtrim(line, " ");
		if (!lexer->arg || ft_strncmp(lexer->arg, "exit", 4) == 0)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		if (lexical_analyzer(lexer) == false)
			err_msg(ERROR_LEXER);
		parser(lexer, parser_utils);
		// t_cmd	*head = parser_utils->cmd_list;
		// int i = 0;
		// while (parser_utils->cmd_list)
		// {
		// 	printf("\n");
		// 	while (parser_utils->cmd_list->data[i])
		// 	{
		// 		printf("	data[%i]	: %s\n", i, parser_utils->cmd_list->data[i]);
		// 		i++;
		// 	}
		// 	printf("	type	: %d\n", parser_utils->cmd_list->type);
		// 	printf("--------------------------\n\n");
		// 	parser_utils->cmd_list = parser_utils->cmd_list->next;
		// }
		// parser_utils->cmd_list = head;
		// g_exit_status = executor(parser_utils, lexer);
		free_token_list(lexer);
		// free_cmd_list(parser_utils);
		free(line);
		// lexer->pipe_num = 0;
		// if (sigint_received == 2)
		// 	exit(0) ;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_lexer_utils	lexer;
	t_parser_utils	parser;
	// int				exit_code;

	//system ("leaks minishell -q");
	argv = NULL;
	if (argc != 1 && argv[0] != NULL)
	{
		printf("Invalid argument.\n");
		exit(EXIT_SUCCESS);
	}
	rl_initialize();
	init_utils(&lexer, &parser);
	signal_handler(PARENT);
	parser.env = createLinkedList(envp);
	parser.envp = join_key_value(parser.env);
	parser.cmd_dirs = get_cmd_dirs(parser.env);
	shell_loop(&lexer, &parser);
	// if (sigint_received == 2)
	// 	exit(0);
	// printf("exit code : %d\n", exit_code);
	destroy_lexer_utils(&lexer);
	destroy_parser_utils(&parser);
	return (0);
}