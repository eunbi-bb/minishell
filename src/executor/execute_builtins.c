#include "minishell.h"
#include "executor.h"

int is_builtin(t_parser_utils *cmd)
{
	if (strcmp(cmd->cmd_list->data[0], "echo") == 0 ||
		strcmp(cmd->cmd_list->data[0], "pwd") == 0 ||
        strcmp(cmd->cmd_list->data[0], "exit") == 0 ||
        strcmp(cmd->cmd_list->data[0], "env") == 0 ||
        strcmp(cmd->cmd_list->data[0], "cd") == 0 ||
        strcmp(cmd->cmd_list->data[0], "export") == 0 ||
        strcmp(cmd->cmd_list->data[0], "unset") == 0)
	{
		printf("BUILT\n");
		return (0);
	}
	else
	{
		printf("NOT BUILT\n");
		return (1);
	}
}

void execute_builtin(t_parser_utils *cmd)
{
	if (strcmp(cmd->cmd_list->data[0], "echo") == 0)
		cmd_echo(cmd->cmd_list->data);
	else if (strcmp(cmd->cmd_list->data[0], "pwd") == 0)
		cmd_pwd();
	else if (strcmp(cmd->cmd_list->data[0], "exit") == 0)
		cmd_exit();
	else if (strcmp(cmd->cmd_list->data[0], "env") == 0)
		cmd_env(*cmd->env);
	else if (strcmp(cmd->cmd_list->data[0], "cd") == 0)
		cmd_cd(cmd->cmd_list->data, *cmd->env);
	else if (strcmp(cmd->cmd_list->data[0], "export") == 0)
		cmd_export(cmd->env, cmd->cmd_list->data[1]);
	else if (strcmp(cmd->cmd_list->data[0], "unset") == 0)
		cmd_unset(cmd->env, cmd->cmd_list->data[1]);
}
