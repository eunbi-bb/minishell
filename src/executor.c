#include "../includes/executor.h"
#include "../includes/parser.h"

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


t_cmd	*call_expander(t_parser_utils *cmd, t_cmd *cmd_list)
{
	t_tokens	*start;

	cmd_list->data = expander(cmd, cmd->data);
	start = cmd_list->redir;
	while (cmd_list->redir)
	{
		if (cmd_list->redir->token != HERE_DOC)
			cmd_list->redir->data = expander_data(cmd, cmd_list->redir->data);
		cmd_list->redir = cmd_list->redir->next;
	}
	cmd_list->redir = start;
	return (cmd);
}

int	pipe_wait(int *pid, int	amount)
{
	int	i;
	int	status;

	i = 0;
	while (i < amount)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	waitpid(pid[i], &status, 0);
	if (WIFEXITED(status))
		g_global.error_num = WEXITSTATUS(status);
	return (EXIT_SUCCESS);
}

int	forking(t_parser_utils *cmd, int end[2], t_cmd *cmd_list)
{
	static int	i;

	if (cmd->reser == TRUE)
	{
		i = 0;
		cmd->reset = FALSE;
	}
	cmd->pid[i] = fork();
	if (cmd->pid[i] < 0)
		error(r, cmd);
	if (cmd->pid[i] == 0)
		dup_cmd(cmd_list, cmd, end, fd_in);
	i++;
	return(EXIT_SUCCESS);
}

int	check_heredoc(t_parser_utils *cmd, int end[2], t_cmd *cmd_list)
{
	int	fd_in;

	if (cmd->heredoc)
	{
		close(end[0]);
		fd_in = open(cmd_list->hd_file_name, O_RDONLY);
	}
	else
		fd_in = end[0];
	return (fd_in);
}

int	executor(t_parser_utils *cmd)
{
	int	end[2];
	int	in;

	in = STDIN_FILENO;
	while (cmd->cmd_list)
	{
		cmd->cmd_list = call_expander(cmd, cmd->cmd_list);
		if (cmd->cmd_list->next)
			pipe(end);
		send_heredoc(cmd, cmd->cmd_list);
		forking(cmd, end, fd_in, cmd->cmd_list);
		close(end[1]);
		if (cmd->cmd_list->prev)
			close(fd_in);
		fd_in = check_heredoc(cmd, end, cmd->cmd_list);
		if (cmd->cmd_list->next)
			cmd->cmd_list = cmd->cmd_list->next;
		else
			break ;
	}
	pipe_wait(cmd->pid, cmd->pipes);
	cmd->cmd_list = simple_cmd(cmd->cmd_list);
	return (0);
}