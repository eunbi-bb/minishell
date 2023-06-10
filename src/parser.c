#include "../includes/parser.h"

int	parser(t_parser_utils *parser)
{
	t_tree_node			*node;
	t_redir_utils	*redir;
	t_lexer_utils	*lexer;
	
	if (lexer->token_list->token == PIPE)
		return (token_error);
	while (lexer->token_list != NULL)
	{
		if (lexer->token_list->token = PIPE)
			//Split tokens depends on pipe.
			split_tokens();
		
	}
	
}