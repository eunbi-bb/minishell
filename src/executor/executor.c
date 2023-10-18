/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 16:13:13 by eucho         #+#    #+#                 */
/*   Updated: 2023/10/18 15:14:21 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "minishell.h"

int	generate_child(t_parser *parser, t_lexer *lexer, int fds[], int i)
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
	t_redir	*current;

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

pid_t	child_process(t_lexer *lexer, t_parser *parser, int fds[], int i)
{
	int		fd_in;
	pid_t	pid;

	fd_in = 0;
	pid = fork();
	signal_handler(CHILD);
	if (pid == -1)
		err_msg(ERROR_CHILD);
	else if (pid == 0)
	{
		fd_in = execute_redir(parser, parser->cmd_list->redir, fd_in);
		g_exit_status = generate_child(parser, lexer, fds, i);
		if (fd_in > 0 && redir_check(parser->cmd_list->redir) == true)
			close(fd_in);
		exit(g_exit_status);
	}
	return (pid);
}

void	executor(t_lexer *lexer, t_parser *parser, int fds[])
{
	pid_t	pid;
	int		i;
	int		built_in;
	t_cmd	*head;

	i = 0;
	built_in = 0;
	head = parser->cmd_list;
	while (parser->cmd_list)
	{
		if (redir_check(parser->cmd_list->redir) == true \
			&& is_builtin(parser) == 0 && lexer->pipe_num == 0)
		{
			g_exit_status = execute_builtin(parser);
			built_in = 1;
			break ;
		}
		pid = child_process(lexer, parser, fds, i);
		parser->cmd_list = parser->cmd_list->next;
		i += 2;
	}
	parser->cmd_list = head;
	close_ends(lexer->pipe_num, fds);
	if (built_in == 0)
		wait_pipes(pid, lexer->pipe_num);
}

void	setup_executor(t_lexer *lexer, t_parser *parser)
{
	int		*fds;

	fds = (int *)malloc(lexer->pipe_num * 2 * sizeof(int));
	if (fds == NULL)
	{
		free(fds);
		err_msg(ERROR_FDS);
	}
	create_pipes(lexer->pipe_num, fds);
	executor(lexer, parser, fds);
	free(fds);
}
