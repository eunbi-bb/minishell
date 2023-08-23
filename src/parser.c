#include "../includes/minishell.h"
#include <readline/readline.h>
#include <stddef.h>

t_cmd	*cmd_lst_front(t_cmd *lst)
{
	t_cmd	*tmp;

	tmp = lst;
	if (!tmp)
		return (tmp);
	while (tmp->prev)
		tmp = tmp->prev;
	return (tmp);
}

t_cmd	*cmd_lst_last(t_cmd *lst)
{
	t_cmd	*tmp;

	tmp = lst;
	if (!tmp)
		return (tmp);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	add_after_cmd(t_cmd *before, t_cmd *new_node)
{
	t_cmd	*head;
	t_cmd	*tail;

	head = cmd_lst_front(before);
	tail = cmd_lst_last(before);
	if (before == NULL)
	{
		new_node->next = head;
		if (head)
			head->prev = new_node;
	}
	else if (before == tail)
	{
		new_node->prev = tail;
		tail->next = new_node;
		tail = new_node;
	}
	else
	{
		new_node->prev = before;
		new_node->next = before->next;
		before->next->prev = new_node;
		before->next = new_node;
	}
}

t_redir	*create_redir_node(void)
{
	t_redir	*redir;

	redir = (t_redir *)ft_calloc(1, sizeof(t_redir));
	redir->file_name = NULL;
	redir->redir_type = DEFAULT;
	redir->next = NULL;
	return (redir); 
}

void	add_after_redir(t_redir **before, t_redir *new_node)
{
	t_redir	*head;

	head = *before;
	if (head == NULL)
	{
		before = &new_node;
	}
	else
	{
		while (head->next != NULL)
			head = head->next;
		head->next = new_node;
	}
}

t_cmd	*create_cmd_node(void)
{
	t_cmd	*new;

	new = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	new->data = NULL;
	new->prev = NULL;
	new->next = NULL;
	return (new); 
}

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
	t_redir		*redir;

	tmp = current;
	while (tmp && tmp->token != PIPE)
	{
		redir = create_redir_node();
		if (cmd->redir == NULL)
			cmd->redir = redir;
		else
			add_after_redir(&cmd->redir, redir);
		redir->redir_type = tmp->token;
		if (tmp->next && tmp->next->token == DEFAULT)
		{
			redir->file_name = ft_strdup(tmp->next->data);
			tmp = tmp->next;
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
	while (i <= arg_num && current)
	{
		if (current->data != NULL && current->token == DEFAULT)
		{
			len = ft_strlen(current->data) + 1;
    		cmd->data[j] = ft_calloc(len, sizeof(char));
    		ft_strlcpy(cmd->data[j], current->data, len);
			j++;
		}
		if (current->token != DEFAULT && current->token != PIPE)
		{
			generate_redir(current, cmd);
		}
		i++;
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
			if (parser->cmd_list == NULL)
			{
				parser->cmd_list = cmd;
			}
			else
			{
				add_after_cmd(parser->cmd_list, cmd);
			}
			generate_cmd(current, cmd);
			while (current->token != PIPE && current->next)
				current = current->next;
		}
		current = current->next;
	}
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
