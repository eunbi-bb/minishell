/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 16:12:41 by eucho         #+#    #+#                 */
/*   Updated: 2023/10/18 14:33:14 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stddef.h>

int	count_args(t_tokens	*lexer)
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

void	generate_redir(t_tokens *curr, t_cmd *cmd)
{
	t_tokens	*tmp;
	t_redir		*new;

	tmp = curr;
	while (tmp && tmp->token != PIPE)
	{
		new = create_redir_node();
		add_after_redir(&cmd->redir, new);
		new->redir_type = tmp->token;
		if (tmp->token >= LESSER && tmp->token <= APPEND)
		{
			curr = curr->next;
			new->file_name = ft_strdup(tmp->next->data);
			tmp = tmp->next;
			curr = curr->next;
		}
		tmp = tmp->next;
	}
}

t_cmd	*generate_cmd(t_tokens *tokens, t_cmd *cmd, int arg_num)
{
	int			i;
	int			j;
	size_t		len;
	t_tokens	*curr;

	i = 0;
	j = 0;
	curr = tokens;
	if (arg_num > 0)
		cmd->data = ft_calloc((arg_num + 1), sizeof(char *));
	generate_redir(curr, cmd);
	while (i++ <= arg_num && curr)
	{
		if (curr->data && (curr->token == DEFAULT || curr->token >= DOLLAR))
		{
			len = ft_strlen(curr->data) + 1;
			cmd->data[j] = ft_calloc(len, sizeof(char));
			ft_strlcpy(cmd->data[j], curr->data, len);
			j++;
		}
		if (curr->token >= LESSER && curr->token <= APPEND)
			curr = curr->next;
		curr = curr->next;
	}
	return (cmd);
}

void	parser(t_lexer *lexer, t_parser *parser)
{
	t_tokens	*curr;
	t_cmd		*cmd;
	int			arg_num;

	curr = lexer->token_list;
	arg_num = count_args(curr);
	while (curr)
	{
		if (curr->token != PIPE)
		{
			cmd = create_cmd_node();
			generate_cmd(curr, cmd, arg_num);
			add_after_cmd(&parser->cmd_list, cmd);
			while (curr->token != PIPE && curr->next)
			{
				curr = curr->next;
			}
		}
		curr = curr->next;
	}
}
