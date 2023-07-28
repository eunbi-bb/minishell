#include "../includes/executor.h"
#include "../includes/parser.h"
#include "../includes/error.h"

static void	create_pipes(t_lexer_utils *lexer, int end[2])
{
	int	i;

	i = 0;
	while (i < lexer->pipe_num)
	{
		if (pipe(end) == -1)
			free_parent();
		i++;
	}
}


// t_cmd	*call_expander(t_parser_utils *cmd, t_cmd *cmd_list)
// {
// 	t_tokens	*start;

// 	cmd_list->data = expander(cmd, cmd->data);
// 	start = cmd_list->redir;
// 	while (cmd_list->redir)
// 	{
// 		if (cmd_list->redir->token != HERE_DOC)
// 			cmd_list->redir->data = expander_data(cmd, cmd_list->redir->data);
// 		cmd_list->redir = cmd_list->redir->next;
// 	}
// 	cmd_list->redir = start;
// 	return (cmd);
// }

int	wait_pipes(int *pid, int pid_num, t_error *error)
{
	int	i;
	int	status;

	i = 0;
	while (i < pid_num)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	waitpid(pid[i], &status, 0);
	if (WIFEXITED(status) == 0)
		error->error_status = WEXITSTATUS(status);
	return (EXIT_SUCCESS);
}

int	forking(t_pipe *pipe, int end[2], t_cmd *cmd_list, int in)
{
	static int	i;

	i = 0;
	if (pipe->reset == TRUE)
	{
		i = 0;
		pipe->reset = FALSE;
	}
	pipe->pid[i] = fork();
	if (pipe->pid[i] < 0)
		err_msg(ERROR_FORK);
	if (pipe->pid[i] == 0)
		dup_cmd(cmd_list, pipe, end, in);
	i++;
	return(EXIT_SUCCESS);
}

int	check_heredoc(t_parser_utils *cmd, int end[2], t_cmd *cmd_list)
{
	int	fd_in;

	if (cmd_list->redir->heredoc)
	{
		close(end[0]);
		fd_in = open(cmd_list->file_name, O_RDONLY);
	}
	else
		fd_in = end[0];
	return (fd_in);
}

int	executor(t_parser_utils *cmd)
{
	t_pipe	pipe;
	int		end[2];
	int		in;

	in = STDIN_FILENO;
	while (cmd->cmd_list)
	{
		if (cmd->cmd_list->next)
			pipe(end);
		// send_heredoc(cmd, cmd->cmd_list);
		forking(&pipe, end, cmd->cmd_list, in);
		close(end[1]);
		if (cmd->cmd_list->prev)
			close(in);
		in = check_heredoc(cmd, end, cmd->cmd_list);
		if (cmd->cmd_list->next)
			cmd->cmd_list = cmd->cmd_list->next;
		else
			break ;
	}
	wait_pipes(&pipe.pid, &pipe.pipes);
	cmd->cmd_list = simple_cmd(cmd->cmd_list);
	return (0);
}