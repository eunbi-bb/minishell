/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_pwd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ssemanco <ssemanco@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 15:35:55 by ssemanco      #+#    #+#                 */
/*   Updated: 2023/06/21 18:01:27 by ssemanco      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void cmd_pwd()
{
    char pwd[PATH_MAX];

    if (getcwd(pwd, sizeof(pwd)) == NULL)
    {
        perror("getcwd");
        exit(-1);
    }
    else
        printf("%s", pwd);
}

int main(int argc, char **argv, char **envp)
{
    //int i = 0;   
    t_env *env = NULL;

    env = createLinkedList(envp);
    if (strcmp(argv[1], "echo") == 0)
        cmd_echo(argc, argv);
    if (strcmp(argv[1], "pwd") == 0)
        cmd_pwd();
    if (strcmp(argv[1], "cd") == 0)
        cmd_cd(argc, argv);
    if (strcmp(argv[1], "export") == 0)
        cmd_export(&env, argv[2]);
    // while (envp[i])
    // {
    //      printf("%s\n", envp[i]);
    //      i++;
    // }
    //cmd_pwd();
    return (0);
}