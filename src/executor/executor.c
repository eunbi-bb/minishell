/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 16:13:13 by eucho         #+#    #+#                 */
/*   Updated: 2023/10/28 21:13:24 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "minishell.h"

static int	execute_child(t_parser *parser, t_lexer *lexer, int fds[], int i)
{
	int		value;

	if (i != 0)
	{
		if (dup2(fds[i - 2], STDIN_FILENO) == -1)
			perror_exit(ERROR_DUP2_IN);
	}
	if (parser->cmd_list->next)
	{
		if (dup2(fds[i + 1], STDOUT_FILENO) == -1)
			perror_exit(ERROR_DUP2_OUT);
	}
	close_ends(lexer->pipe_num, fds);
	value = execute_command(parser);
	return (value);
}

/*
*	Check if the redir linked list contains redir_type.
*	Return true if it contains it, otherwise return false.
*/
static bool	redir_check(t_redir *redir)
{
	t_redir	*current;

	current = redir;
	if (redir == NULL)
		return (false);
	while (current != NULL)
	{
		if (current->redir_type >= LESSER && current->redir_type <= APPEND)
			return (true);
		current = current->next;
	}
	return (false);
}

/*
*	Generate child processes. Initially, redirect based on the command and 
*	then execute the command. The 'execute_child' will return an 'exit_code' 
*	based on its status. This 'exit_code' is stored in 'g_exit_status' and 
*	will later be used in the expander for the '$?' character.
*/
pid_t	child_process(t_lexer *lexer, t_parser *parser, int fds[], int i)
{
	// int		fd_in;
	pid_t	pid;

	// fd_in = 0;
	pid = fork();
	if (lexer->heredoc == true)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		lexer->heredoc = false;
	}
	else
		signal_handler(CHILD);
	if (pid == -1)
		err_msg(ERROR_CHILD);
	else if (pid == 0)
	{
		// if (parser->cmd_list->redir != NULL && parser->cmd_list == NULL)
		// 	fd_in = execute_redir(parser, parser->cmd_list->redir, fd_in);
		// if (fd_in > 0 && redir_check(parser->cmd_list->redir) == false)
		// 	close(fd_in);
		g_exit_status = execute_child(parser, lexer, fds, i);
		exit(g_exit_status);
	}
	return (pid);
}

/*
*	Execute commands. If the input consists of only one built-in command 
*	without redirecion, execute that command and terminate the executor. 
*	Otherwise, generate child processes and execute them inside.
*	The 'built_in' variable  is used to determine whether the parent process
*	needs to wait for child processes or not.
*	'i' increments every 2 to redirect STDIN(even number) and STDOUT(odd number)
	inside the 'child_process()'.
*/
static void	executor(t_lexer *lexer, t_parser *parser, int fds[])
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
		if (redir_check(parser->cmd_list->redir) == false \
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
	close_ends(lexer->pipe_num, fds);
	if (built_in == 0)
		wait_pipes(pid, lexer->pipe_num);
	parser->cmd_list = head;
}

/* 
*	Set up for executing commands.
*	This involves allocating pipe file descriptors, creating pipes,
*	and launching the 'executor()'.
*/
void	setup_executor(t_lexer *lexer, t_parser *parser)
{
	int		*fds;

	fds = malloc(lexer->pipe_num * 2 * sizeof(int));
	if (fds == NULL)
	{
		free(fds);
		err_msg(ERROR_FDS);
	}
	create_pipes(lexer->pipe_num, fds);
	executor(lexer, parser, fds);
	free(fds);
}
