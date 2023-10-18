/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 16:12:41 by eucho         #+#    #+#                 */
/*   Updated: 2023/10/19 00:11:08 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stddef.h>

static int	count_args(t_tokens	*lexer)
{
	int			arg_num;
	t_tokens	*tmp;

	tmp = lexer;
	arg_num = 0;
	while (tmp != NULL)
	{
		if (tmp->token == PIPE)
			break ;
		arg_num++;
		if (tmp->token >= LESSER && tmp->token <= APPEND)
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
		add_after_redir(&cmd->redir, new);
		new->redir_type = tmp->token;
		if (tmp->token >= LESSER && tmp->token <= APPEND)
		{
			current = current->next;
			new->file_name = ft_strdup(tmp->next->data);
			tmp = tmp->next;
			current = current->next;
		}
		tmp = tmp->next;
	}
}

t_cmd	*generate_cmd(t_tokens *tokens, t_cmd *cmd)
{
	int			arg_num;
	int			i;
	int			j;
	size_t		len;
	t_tokens	*current;

	i = 0;
	j = 0;
	current = tokens;
	arg_num = count_args(current);
	if (arg_num > 0)
		cmd->data = ft_calloc((arg_num + 1), sizeof(char *));
	generate_redir(current, cmd);
	while (i <= arg_num && current)
	{
		if (current->data != NULL && (current->token == DEFAULT || current->token >= DOLLAR))
		{
			len = ft_strlen(current->data) + 1;
			cmd->data[j] = ft_calloc(len, sizeof(char));
			ft_strlcpy(cmd->data[j], current->data, len);
			j++;
		}
		i++;
		if (current->token >= LESSER && current->token <= APPEND)
			current = current->next;
		current = current->next;
	}
	return (cmd);
}

/*
*	Generating a command list based on PIPE('|') symbol.
*/
void	parser(t_lexer *lexer, t_parser *parser)
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
			add_after_cmd(&parser->cmd_list, cmd);
			while (current->token != PIPE && current->next)
			{
				current = current->next;
			}
		}
		current = current->next;
	}
}

