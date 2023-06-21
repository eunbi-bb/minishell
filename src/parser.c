#include "../includes/parser.h"

// void	init_parser_utils(t_lexer_utils *lexer, t_parser_utils *parser)
// {
// 	t_redir_utils	redir;

// 	redir.lexer_lst = lexer->token_list;
// 	redir.redir = NULL;
// 	redir.num_redir = 0;
// 	redir.utils = parser;
// 	return (redir);
// }
t_cmd	*create_cmd_node(char *data)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	new->data = data;
	new->next = NULL;
	return (new); 
}

// t_cmd	*add_node_tree(t_cmd *root, char *data)
// {
// 	if (root = NULL)
// 		root = create_node(data);
// 	else if ()
// 		root->left = add_node_tree(root->left, data);
// 	else if ()
// 		root->right = add_node_tree(root->right, data);
// 	return (root);
// }

t_cmd	generate_simple_cmd(t_lexer_utils *lexer)
{
	t_cmd		*cmd;
	t_tokens	*current;

	current = lexer->token_list;
	args = (t_node *)malloc(sizeof(t_node));
	args->str = ft_strdup("");
	while (current != NULL)
	{
		while (current->token == -1)
		{
			args->str = ft_strjoin(args->str, current->data);
			args->str = ft_strjoin(args->str, " ");
		}
		ft_strtrim(args->str, " ");
		current = current->next;
		free(current);
		args = args->next;
	}
	return (*args);
}


int	parser(t_parser_utils *parser)
{
	t_node	*node;
	t_lexer_utils	*lexer;
	
	// if (lexer->token_list->token == PIPE)
	// 	return (token_error);

	//If there is no pipes or any tokens. It's ready to execute.
	if (lexer->pipe_num == 0)
	{
		generate_simple_cmd(&lexer);
	}

	while (lexer->token_list != NULL)
	{
		if (lexer->token_list->token == PIPE)
		//init_parser_utils(&lexer, &parser);
	}
}
	
