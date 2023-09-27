#include "minishell.h"
#include <readline/readline.h>
#include <stddef.h>

int	count_args(t_tokens	*lexer)
{
	int	arg_num;
	t_tokens	*tmp;

	tmp = lexer;
	arg_num = 0;
	while (tmp != NULL)
	{
		if (tmp->token == PIPE)
			break ;
		arg_num++;
		if (tmp->token != PIPE && tmp->token != DEFAULT)
			arg_num -= 2;
		tmp = tmp->next;
	}
	return (arg_num);
}

void	generate_redir(t_tokens *current, t_cmd *cmd)
{
	t_tokens	*tmp;
	t_redir		*new;

	tmp = current;
	while (tmp && tmp->token != PIPE)
	{
		new = create_redir_node();
		// if (cmd->redir == NULL)
		// 	cmd->redir = new;
		// else if (cmd->redir != NULL && tmp->token != PIPE && tmp->token != DEFAULT)
			add_after_redir(&cmd->redir, new);
		new->redir_type = tmp->token;
		if (tmp->token >= 1)
		{
			current = current->next;
			new->file_name = ft_strdup(tmp->next->data);
			tmp = tmp->next;
			current = current->next;
		}
		tmp = tmp->next;
	}
	//free_tokens_list(tmp);
}

t_cmd	*generate_cmd(t_tokens *current, t_cmd *cmd)
{
	int			arg_num;
	int			i;
	int			j;
	size_t		len;

	i = 0;
	j = 0;
	arg_num = count_args(current);
	if (arg_num > 0)
		cmd->data = ft_calloc((arg_num + 1), sizeof(char *));
	generate_redir(current, cmd);
	while (i <= arg_num && current)
	{
		if (current->data != NULL && current->token == DEFAULT)
		{
			len = ft_strlen(current->data) + 1;
			cmd->data[j] = ft_calloc(len, sizeof(char));
			ft_strlcpy(cmd->data[j], current->data, len);
			j++;
		}
		i++;
		if (current->token != DEFAULT && current->token != PIPE)
			current = current->next;
		current = current->next;
	}
	return (cmd);
}

void	parser(t_lexer_utils *lexer, t_parser_utils *parser)
{
	t_tokens	*current;
	t_cmd		*cmd;

	current = lexer->token_list;
	while (current)
	{
		if (current->token != PIPE)
		{
			cmd = create_cmd_node();
			generate_cmd(current, cmd);
			// if (parser->cmd_list == NULL)
			// {
			// 	add_after_cmd(&parser->cmd_list, cmd);
			// }
			// else
			// {
				add_after_cmd(&parser->cmd_list, cmd);
			// }
			while (current->token != PIPE && current->next)
			{
				current = current->next;
			}
		}
		current = current->next;
	}
	destroy_lexer_list(&lexer->token_list);
}

// int	main(void)
// {
// 	t_lexer_utils lexer;
// 	t_parser_utils parser_list;
// 	char	*str;

// 	str = readline("Minishell% ");
// 	lexer.arg = ft_strtrim(str, " ");
// 	if (match_quotes(lexer.arg) == FALSE)
// 		return (-1);
// 	lexer.pipe_num = 0;
// 	lexical_analyzer(&lexer);

// 	// /***** PRINT LEXER *****/
// 	// printf("\n");
// 	// printf("INPUT : %s\n\n", str);
// 	// printf("NUMBER OF PIPES : %i\n", lexer.pipe_num);
// 	// printf("HEREDOC ACTIVE : %d\n", lexer.heredoc);

// 	// t_tokens *curr = lexer.token_list;
// 	// int i = 1;
// 	// while (curr != NULL)
// 	// {
// 	// 	printf("%d. curr->data: %s\n", i, curr->data);
// 	// 	printf("%d. curr->token: %d\n", i, curr->token);
// 	// 	curr = curr->next;
// 	// 	i++;
// 	// 	printf("\n");
// 	// }
// 	parser(&lexer, &parser_list);
// 	if (lexer.heredoc == TRUE)
// 	{
// 		here_document(parser_list.cmd_list, &lexer);
// 	}

		
// 	/***** PRINT PARSER ****/
// 	t_cmd	*current = parser_list.cmd_list;

// 	int n = 1;

// 	while (current)
// 	{
// 		printf("\n--------Number of command : %d---------\n", n);
// 		int	arg_num = count_args(lexer.token_list);
// 		int i = 0;
// 		if (current->data && current->data[i] != NULL)
// 		{
// 			while (current->data[i] && i <= arg_num)
// 			{
// 				printf("cmd->data[%d] : %s\n", i, current->data[i]);
// 				i++;
// 			}
// 		}
// 		if (current->redir)
// 		{
// 			t_redir *cmd_redir = current->redir;
// 			while (cmd_redir)
// 			{
// 				printf("cmd->redir_type : %d\n", cmd_redir->redir_type);
// 				printf("cmd->filename : %s\n", cmd_redir->file_name);
// 				cmd_redir = cmd_redir->next;
// 			}
// 		}
// 		current = current->next;
// 		n++;
// 	}
// 	free (str);
// 	return (0);
// }
