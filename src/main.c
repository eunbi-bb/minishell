/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 16:11:54 by eucho         #+#    #+#                 */
/*   Updated: 2023/10/02 19:20:04 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "error.h"

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

int	shell_loop(t_lexer_utils *lexer, t_parser_utils	*parser_utils)
{
	char			*line;
	int				status;

	status = 0;
	rl_catch_signals = 0;
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
		perror_exit(ERROR_SIG);
	signal(SIGQUIT, SIG_IGN);
	while (status == 0 || status == 127)
	{
		if (sigint_received)
            sigint_received = 0; // Reset the flag
		line = readline_loop();
		lexer->arg = ft_strtrim(line, " ");
		if (!lexer->arg || ft_strncmp(lexer->arg, "exit", 4) == 0)
		{
			free(line);
			write(STDOUT_FILENO, "exit\n", 6);
			exit(EXIT_SUCCESS);
		}
		if (lexical_analyzer(lexer) == false)
			return (err_msg(ERROR_LEXER));
		parser(lexer, parser_utils);
		status = executor(parser_utils, lexer);
		free_token_list(lexer);
		free_cmd_list(parser_utils);
		free(line);
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
	parser.envp = join_key_value(parser.env);
	parser.cmd_dirs = get_cmd_dirs(parser.env);
	exit_code = shell_loop(&lexer, &parser);
	if (sigint_received == 2)
		exit(0);
	// printf("exit code : %d\n", exit_code);
	destroy_lexer_utils(&lexer);
	destroy_parser_utils(&parser);
	return (exit_code);
}