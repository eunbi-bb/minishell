/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_pwd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ssemanco <ssemanco@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 15:35:55 by ssemanco      #+#    #+#                 */
/*   Updated: 2023/05/24 19:02:25 by ssemanco      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void cmd_pwd()
{
    char pwd[4500];

    if (getcwd(pwd, sizeof(pwd)) == NULL)
    {
        perror("getcwd");
        exit(-1);
    }
    else
        printf("%s\n", pwd);
}

int main(int argc, char **argv, char **envp)
{
    int i = 0;
    
    argc = 0;
    argv = NULL;
    while (envp[i])
    {
         printf("%s\n", envp[i]);
         i++;
    }
    cmd_pwd();
    return (0);
}