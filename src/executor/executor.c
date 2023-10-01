#include "executor.h"
#include "parser.h"
#include "error.h"
#include "minishell.h"

int child;

int	execute_redir(t_parser_utils *parser, t_lexer_utils *lexer, t_redir *redir)
{
	int	fd_in;
	t_redir	*head;

	head = redir;
	fd_in = 0;
	while (redir)
	{
		if (redir != NULL && redir->redir_type == HERE_DOC)
			here_document(parser->cmd_list, lexer);
		if (redir != NULL && redir->redir_type != DEFAULT)
			fd_in = redirection(parser->cmd_list);
		redir = redir->next;
	}
	redir = head;
	return (fd_in);
}

int	execute_command(t_parser_utils *parser)
{
	if (is_builtin(parser) == 0)
	{
		execute_builtin(parser);
		return (0);
	}
	else  
	{
		if (generate_command(parser) == EXIT_CMD)
			return (EXIT_CMD);
		if (execve(parser->command, parser->cmd_list->data, parser->envp) < 0)
		{
			perror_exit(ERROR_EXECVE);
		}
	}
	return (1);
}

int	generate_child(t_parser_utils *parser, t_lexer_utils *lexer, int fds[], int i)
{
	int	fd_in;
	int	value;

	fd_in = execute_redir(parser, lexer, parser->cmd_list->redir);
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
	find_usd(parser->cmd_list->data, *parser->env);
	value = execute_command(parser);
	if (fd_in > 0)
		close(fd_in);
	return (value);
}

int	executor(t_parser_utils *parser, t_lexer_utils *lexer)
{
	int		fds[lexer->pipe_num * 2];
	pid_t	pid;
	int		i;
	t_cmd	*head;
	int		value;
	
	head = parser->cmd_list;
	i = 0;
	create_pipes(lexer->pipe_num, fds);
	while (parser->cmd_list != NULL)
	{
		pid = fork();
		child = 1;
		signal(SIGQUIT, sigquit_handler);
		if (pid == -1)	err_msg(ERROR_CHILD);
		else if (pid == 0)
		{
			value = generate_child(parser, lexer, fds, i);
			if (value != 1)
				return (value);
		}
		parser->cmd_list = parser->cmd_list->next;
		i += 2;
	}
	parser->cmd_list = head;
	close_ends(lexer->pipe_num, fds);
	return (wait_pipes(pid, lexer->pipe_num));
}
