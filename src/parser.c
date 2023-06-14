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

t_node	split_tokens(t_lexer_utils *lexer)
{
	t_node		*args;
	t_tokens	*current;

	current = lexer->token_list;
	args = (t_node *)malloc(sizeof(t_node));
	args->str = ft_strdup("");
	while (current != NULL)
	{
		while (current->token == NULL)
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
	while (lexer->token_list != NULL)
	{
		if (lexer->token_list->token == PIPE)
			//Split tokens depends on tokens. Put all the data in a str(to put execve()).
			split_tokens(&lexer);
		//init_parser_utils(&lexer, &parser);
	}
	
