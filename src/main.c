/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 16:11:54 by eucho         #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2023/10/18 20:02:23 by ssemanco      ########   odam.nl         */
=======
/*   Updated: 2023/10/18 19:13:29 by eucho         ########   odam.nl         */
>>>>>>> fff6768bd6dd792531373fbfadcb3bcf50e9d55d
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "error.h"

int	g_exit_status;

void	init_utils(t_lexer *lexer, t_parser	*parser, t_data *data)
{
	lexer->pipe_num = 0;
	lexer->heredoc = false;
	lexer->token_list = NULL;
	parser->cmd_list = NULL;
	parser->pid = 0;
	parser->env = NULL;
	data->eq_sign = NULL;
	data->env = NULL;
	data->key_len = 0;
	data->key = NULL;
	data->value = NULL;
	data->new_node = NULL;
	data->i = 0;
}

/*
*	Set up a loop for reading user input,
*	handling scenarios where the user wants to exit or enters an empty line.
*	It also maintains a command history using the Readline library,
*	allowing the user to navigate and reuse previous commands.
*	if (!line) : Check if line is NULL, which happens if the user presses Ctrl+D.
*	if (!*line): If the line is empty, it frees the memory allocated for line 
*					and then calls readline_loop() recursively.
*	if (*line): If the input line is not empty (i.e., the user entered a command), 
*				it adds the input line to the command history using add_history.
*				This allows to recall and reuse previously entered commands.
*/
static char	*readline_loop(void)
{
	char	*line;

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

static void	run_shell(t_lexer *lexer, t_parser *parser_utils, t_env *env)
{
	parser_utils->envp = join_key_value(parser_utils->env);
	parser_utils->cmd_dirs = get_cmd_dirs(parser_utils->env);
	if (lexical_analyzer(lexer) == false)
		err_msg(ERROR_LEXER);
	expand(lexer->token_list, env);
	parser(lexer, parser_utils);
	setup_executor(lexer, parser_utils);
}

/*
*	Obtain input from the prompt through readline_loop()
*	and if the input passes input_check(), then proceed to run Minishell.
*/
static void	shell_loop(t_lexer *lexer, t_parser	*parser, t_env *env)
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

void init_data(t_data *data)
{
	data->eq_sign = NULL;
	data->env = NULL;
	data->key_len = 0;
	data->key = NULL;
	data->value = NULL;
	data->new_node = NULL;
	data->i = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_lexer		lexer;
	t_parser	parser;
	t_data		data;

	argv = NULL;
	if (argc != 1 && argv[0] != NULL)
	{
		printf("Invalid argument.\n");
		exit(EXIT_SUCCESS);
	}
	rl_initialize();
	init_utils(&lexer, &parser, &data);
	parser.env = create_link_list(envp, &data);
	shell_loop(&lexer, &parser, *parser.env);
	destroy_lexer_parser(&lexer, &parser);
	return (0);
}
