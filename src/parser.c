#include "../includes/parser.h"

void	init_parser_utils(t_lexer_utils *lexer, t_parser_utils *parser)
{
	t_redir_utils	redir;

	redir.lexer_lst = lexer->token_list;
	redir.redir = NULL;
	redir.num_redir = 0;
	redir.utils = parser;
	return (redir);
}


int	parser(t_parser_utils *parser)
{
	t_parser_node	*node;
	t_lexer_utils	*lexer;
	
	if (lexer->token_list->token == PIPE)
		return (token_error); 
	while (lexer->token_list != NULL)
	{
		if (lexer->token_list->token == PIPE)
			//Split tokens depends on pipe.
			split_tokens(&lexer);
		init_parser_utils(&lexer, &parser);
	}
	
}