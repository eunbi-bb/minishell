/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_pwd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ssemanco <ssemanco@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 15:35:55 by ssemanco      #+#    #+#                 */
/*   Updated: 2023/08/16 13:02:43 by ssemanco      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void cmd_pwd()
{
    char pwd[PATH_MAX];

    if (getcwd(pwd, sizeof(pwd)) == NULL)
    {
        perror("getcwd");
        exit(-1);
    }
    else
        printf("%s\n", pwd);
}
