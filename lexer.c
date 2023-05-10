#include "lexer.h"


void	lexer(char *arg)
{
	char *tokens;
	int	i;

	i = 0;
	if (arg[i] == ' ')
		tokens[i] = BLANK;
	else if (arg[i] == '|')
		tokens[i] = PIPE;
	else if (arg[i] == )
}

int	main(int argc, char **argv, char *envp[])
{
	int	i;
	char *args;

	lexer(argv[2]);
}