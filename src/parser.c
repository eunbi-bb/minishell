#include "../includes/parser.h"
#include <readline/readline.h>

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

void	add_after_redir(t_redir **before, t_redir *new_node)
{
	t_redir	*head;

	head = *before;//lst_front(before);
	if (head == NULL)
	{
		*before = new_node;
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

	new = (t_cmd *)malloc(sizeof(t_cmd));
	new->redir = (t_redir *)malloc(sizeof(t_redir));
	new->data = NULL;
	new->redir->file_name = NULL;
	new->redir->redir_type = DEFAULT;
	new->redir->next = NULL;
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
	while (tmp)
	{
		if (tmp->token == PIPE)
			break ;
		arg_num++;
		tmp = tmp->next;
	}
	return (arg_num);
}

t_cmd	*generate_cmd(t_tokens *current, t_cmd *cmd)
{
	int			arg_num;
	int			i;

	i = 0;
	arg_num = count_args(current);
	cmd->data = malloc(arg_num * sizeof(char *));
	while (i < arg_num)
	{
		if (current->data != NULL)
		{
			printf("data\n");
			cmd->data[i] = malloc((ft_strlen(current->data) + 1) * sizeof(char));
			ft_strlcpy(cmd->data[i], current->data, (ft_strlen(current->data) + 1));
		}
		// printf ("cmd.data[%d] : %s\n", i, cmd.data[i]);
		if (current->token != DEFAULT)
		{
			printf("redir\n");
			cmd->redir->redir_type = current->token;
			printf("cmd.redir : %d\n", cmd->redir->redir_type);
			if (current->next)
				cmd->redir->file_name = ft_strdup(current->next->data);
		}
		i++;
		current = current->next;
	}
	return (cmd);
}

void	parser(t_lexer_utils *lexer)
{
	t_parser_utils	parser;
	t_tokens	*current;
	t_cmd		*cmd;

	current = lexer->token_list;
	parser.cmd_list = NULL;
	while (current)
	{
		if (current->token != PIPE)
		{
			cmd = create_cmd_node();
			if (parser.cmd_list != NULL)
				parser.cmd_list = cmd;
			else
				add_after_cmd(parser.cmd_list, cmd);
			generate_cmd(current, cmd);
			while (current->token != PIPE && current->next)
				current = current->next;
		}
		current = current->next;
	}
}

int	main(void)
{
	t_lexer_utils lexer;
	char	*str;

	// str = readline("parser> ");
	str = "    < infile grep -p 'Hello World' | cat -e > outfile    ";
	// str = "    grep -p 'Hello World' | cat -e   ";
	lexer.arg = ft_strtrim(str, " ");
	if (match_quotes(lexer.arg) == FALSE)
		return (-1);
	lexer.pipe_num = 0;
	lexical_analyzer(&lexer);
	// Print lexer
	// printf("\n");
	// printf("INPUT : %s\n\n", str);
	// printf("NUMBER OF PIPES : %i\n", lexer.pipe_num);

	// t_tokens *current = lexer.token_list;
	// int i = 1;
	// while (current != NULL)
	// {
	// 	printf("%d. current->data: %s\n", i, current->data);
	// 	printf("%d. current->token: %d\n", i, current->token);
	// 	current = current->next;
	// 	i++;
	// 	printf("\n");
	// }
	parser(&lexer);
	
	return (0);
}
