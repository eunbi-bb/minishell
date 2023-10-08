/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 16:13:13 by eucho         #+#    #+#                 */
/*   Updated: 2023/10/08 18:00:58 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "parser.h"
#include "error.h"
#include "minishell.h"

int	execute_redir(t_parser_utils *parser, t_redir *redir)
{
	int	fd_in;
	t_redir	*head;

	head = redir;
	fd_in = 0;
	while (redir)
	{
		if (redir != NULL && redir->redir_type == HERE_DOC)
		{
			signal_handler(HEREDOC);
			here_document(parser->cmd_list);
			if (!parser->cmd_list->data)
				exit(EXIT_SUCCESS);
		}
		if (redir != NULL && redir->redir_type != DEFAULT)
		{
			fd_in = redirection(parser->cmd_list->redir);
		}
		redir = redir->next;
	}
	redir = head;
	return (fd_in);
}

int	execute_command(t_parser_utils *parser)
{
	if (parser->cmd_list->data)
	{
		if (is_builtin(parser) == 0)
		{
			execute_builtin(parser);
			return (0);
		}
		else
		{
			if (generate_command(parser) == EXIT_CMD)
			{
				g_exit_status = EXIT_CMD;
				exit(EXIT_SUCCESS);
			}
			if (parser->cmd_list->data)
			{
				if (execve(parser->command, parser->cmd_list->data, parser->envp) < 0)
				{
					perror_exit(ERROR_EXECVE);
				}
			}
		}
		return (1);
	}
	return (0);
}

int	generate_child(t_parser_utils *parser, t_lexer_utils *lexer, int fds[], int i)
{
	int	value;
	t_cmd	*head;

	head = parser->cmd_list;
	while (parser->cmd_list)
	{
		if (i != 0)
		{
			if (dup2(fds[i - 2], 0) == -1)
				perror_exit(ERROR_DUP2_IN);
		}
		if (parser->cmd_list->next)
		{
			if (dup2(fds[i + 1], 1) == -1)
				perror_exit(ERROR_DUP2_OUT);
		}
		close_ends(lexer->pipe_num, fds);
		value = execute_command(parser);
		parser->cmd_list = parser->cmd_list->next;
	}
	parser->cmd_list = head;
	return (value);
}

int	executor(t_parser_utils *parser, t_lexer_utils *lexer)
{
	int		fds[lexer->pipe_num * 2];
	int		fd_in;
	pid_t	pid;
	int		i;
	t_cmd	*head;
	int		value;
	
	head = parser->cmd_list;
	i = 0;
	create_pipes(lexer->pipe_num, fds);
	while (parser->cmd_list != NULL)
	{
		if (parser->cmd_list->data)
			find_usd(parser->cmd_list->data, *parser->env);
		if (parser->cmd_list->data && is_builtin(parser) == 0)
			return (execute_builtin(parser));
		pid = fork();
		if (pid == -1)
			err_msg(ERROR_CHILD);
		else if (pid == 0)
		{
			signal_handler(CHILD);
			fd_in = execute_redir(parser, parser->cmd_list->redir);
			value = generate_child(parser, lexer, fds, i);
			if (value != 1)
				return (value);
			if (fd_in > 0)
				close(fd_in);
		}
		parser->cmd_list = parser->cmd_list->next;
		i += 2;
	}
	parser->cmd_list = head;
	close_ends(lexer->pipe_num, fds);
	return (wait_pipes(pid, lexer->pipe_num));
}
