/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 16:11:54 by eucho         #+#    #+#                 */
/*   Updated: 2023/10/17 23:16:33 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "error.h"

int	g_exit_status;

void	init_utils(t_lexer_utils *lexer, t_parser_utils	*parser)
{
	lexer->pipe_num = 0;
	lexer->heredoc = false;
	lexer->token_list = NULL;
	parser->cmd_list = NULL;
	parser->pid = 0;
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

void	run_shell(t_lexer_utils *lexer, t_parser_utils *parser_utils, t_env *env)
{
	parser_utils->envp = join_key_value(parser_utils->env);	
	parser_utils->cmd_dirs = get_cmd_dirs(parser_utils->env);
	if (lexical_analyzer(lexer) == false)
		err_msg(ERROR_LEXER);
	expand(lexer->token_list, env);
	parser(lexer, parser_utils);
	executor(parser_utils, lexer);
}


void	shell_loop(t_lexer_utils *lexer, t_parser_utils	*parser, t_env *env)
{
	char			*line;

	g_exit_status = 0;
	while (g_exit_status >= 0)
	{
		signal_handler(PARENT);
		line = readline_loop();
		if (line)
			lexer->arg = ft_strtrim(line, " ");
		else
			lexer->arg = line;
		if (!lexer->arg || ft_strncmp(lexer->arg, "exit", 4) == 0)
		{
			free(line);
			write(STDOUT_FILENO, "exit\n", 5);
			exit(EXIT_SUCCESS);
		}
		if (input_check(lexer->arg) == false)
			free_prev_line(lexer, line);
		else
		{
			run_shell(lexer, parser, env);
			reset(lexer, parser, line);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_lexer_utils	lexer;
	t_parser_utils	parser;

	argv = NULL;
	if (argc != 1 && argv[0] != NULL)
	{
		printf("Invalid argument.\n");
		exit(EXIT_SUCCESS);
	}
	rl_initialize();
	init_utils(&lexer, &parser);
	parser.env = createLinkedList(envp);
	// parser.cmd_dirs = get_cmd_dirs(parser.env);
	shell_loop(&lexer, &parser, *parser.env);
	destroy_lexer_utils(&lexer);
	destroy_parser_utils(&parser);
	return (0);
}