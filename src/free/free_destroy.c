/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_destroy.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/15 19:42:20 by eucho         #+#    #+#                 */
/*   Updated: 2023/10/19 22:34:02 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Free the previous input line if the input_check() fails
void	free_prev_line(t_lexer *lexer, char *line)
{
	free(line);
	free(lexer->arg);
}

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

void	free_cmd_dirs(t_parser *parser)
{
	int	i;

	i = 0;
	while (parser->cmd_dirs[i])
	{
		free(parser->cmd_dirs[i]);
		i++;
	}
	free(parser->cmd_dirs);
}

// Clean up data before quitting the program.
void	destroy_lexer_parser(t_lexer *lexer, t_parser *parser)
{
	free_token_list(lexer);
	free(lexer->type_arr);
	free_cmd_list(parser);
	free(parser->args);
	free_env_list(parser);
	if (parser->cmd_dirs)
		free_cmd_dirs(parser);
	free_envp(parser->envp);
	free(parser->command);
}

// Reset data for the next inserted input.
void	reset(t_lexer *lexer, t_parser *parser, char *line)
{
	free_token_list(lexer);
	free_cmd_list(parser);
	free_envp(parser->envp);
	if (parser->cmd_dirs)
		free_cmd_dirs(parser);
	free(line);
	lexer->pipe_num = 0;
}
