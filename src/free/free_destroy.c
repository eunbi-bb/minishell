/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_destroy.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/15 19:42:20 by eucho         #+#    #+#                 */
/*   Updated: 2023/10/15 20:49:45 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_prev_line(t_lexer_utils *lexer, char *line)
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

void	destroy_parser_utils(t_parser_utils *parser)
{
	int	i;

	free_cmd_list(parser);
	free(parser->args);
	free_env_list(parser);
	free_envp(parser->envp);
	i = 0;
	while (parser->cmd_dirs[i])
	{
		free(parser->cmd_dirs[i]);
		i++;
	}
	free(parser->cmd_dirs);
	free(parser->command);
}

void	destroy_lexer_utils(t_lexer_utils *lexer)
{
	free_token_list(lexer);
	free(lexer->type_arr);
}

void	reset(t_lexer_utils *lexer, t_parser_utils *parser, char *line)
{
	free_token_list(lexer);
	free_cmd_list(parser);
	free_envp(parser->envp);
	free(line);
	lexer->pipe_num = 0;
}