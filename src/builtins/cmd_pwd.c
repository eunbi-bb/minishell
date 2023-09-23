/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_pwd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ssemanco <ssemanco@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 15:35:55 by ssemanco      #+#    #+#                 */
/*   Updated: 2023/09/23 18:13:41 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int cmd_pwd()
{
    char pwd[PATH_MAX];

    if (getcwd(pwd, sizeof(pwd)) == NULL)
    {
        perror("getcwd");
        return(-1);
    }
    else
    {
          printf("%s\n", pwd);
          return(0);
    }  
}
