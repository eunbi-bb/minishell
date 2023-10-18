/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_free.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ssemanco <ssemanco@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/18 21:31:54 by ssemanco      #+#    #+#                 */
/*   Updated: 2023/10/18 21:34:52 by ssemanco      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_sorted(t_env *head)
{
	t_env *current;
	t_env *next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
}
