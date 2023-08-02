/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_cd.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ssemanco <ssemanco@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/07 11:36:32 by ssemanco      #+#    #+#                 */
/*   Updated: 2023/08/02 16:37:35 by ssemanco      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void cmd_cd( char **path) 
{
    //printf("%s\n", path[2]);
    if (chdir(path[2]) == -1)
    {
        perror("chdir");
        exit(-1);
    }
    //cmd_pwd();
}

//what does cd with no arg do