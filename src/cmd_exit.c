/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_exit.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ssemanco <ssemanco@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 13:03:25 by ssemanco      #+#    #+#                 */
/*   Updated: 2023/08/16 13:09:42 by ssemanco      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void cmd_exit()
{
    //free if necessary
    printf("got here \n");
    exit(1); //exit with status
}