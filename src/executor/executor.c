/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 16:13:13 by eucho         #+#    #+#                 */
/*   Updated: 2023/10/15 17:26:14 by eucho         ########   odam.nl         */
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
			return execute_builtin(parser);
		else
		{
			if (generate_command(parser) == EXIT_CMD)
				return (EXIT_CMD);
			else
			{
				if (parser->cmd_list->data)
				{
					if (execve(parser->command, parser->cmd_list->data, parser->envp) < 0)
						perror_exit(ERROR_EXECVE);
				}
			}
		}
	}
	return(EXIT_SUCCESS);
}

int	generate_child(t_parser_utils *parser, t_lexer_utils *lexer, int fds[], int i)
{
	t_cmd	*head;
	int		value;

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

bool	redir_check(t_redir *redir)
{
	t_redir *current;

	current = redir;
	if (redir == NULL)
		return (true);
	while (current != NULL)
	{
		if (current->redir_type >= LESSER && current->redir_type <= APPEND)
			return (false);
		current = current->next;
	}
	return (true);
}

void	executor(t_parser_utils *parser, t_lexer_utils *lexer)
{
	int		fds[lexer->pipe_num * 2];
	int		fd_in;
	pid_t	pid;
	int		i;
	t_cmd	*head;
	int		built_in;

	head = parser->cmd_list;
	built_in = 0;
	i = 0;
	create_pipes(lexer->pipe_num, fds);
	while (parser->cmd_list)
	{
		if (parser->cmd_list->data && redir_check(parser->cmd_list->redir) == true && is_builtin(parser) == 0)
		{
			built_in = 1;
			g_exit_status = execute_builtin(parser);
			break ;
		}
		pid = fork();
		if (pid == -1)
			err_msg(ERROR_CHILD);
		else if (pid == 0)
		{
			signal_handler(CHILD);
			fd_in = execute_redir(parser, parser->cmd_list->redir);
			g_exit_status = generate_child(parser, lexer, fds, i);
			if (fd_in > 0 && redir_check(parser->cmd_list->redir) == true)
				close(fd_in);
			exit(g_exit_status);
		}
		parser->cmd_list = parser->cmd_list->next;
		i += 2;
	}
	parser->cmd_list = head;
	close_ends(lexer->pipe_num, fds);
	// printf("exit code1: %d\n", g_exit_status);
	if (built_in == 0)
		wait_pipes(pid, lexer->pipe_num, built_in);
	// printf("exit code2: %d\n", g_exit_status);
}
