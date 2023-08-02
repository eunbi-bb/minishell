/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_echo.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ssemanco <ssemanco@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/03 11:06:15 by ssemanco      #+#    #+#                 */
/*   Updated: 2023/06/07 11:32:05 by ssemanco      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int cmd_echo(int argc, char **data) // argv = cmd 
{
    int printNewline = 1;
    int i;

    //i = 2;
    if (argc > 1 && strcmp(argv[2], "-n") == 0) //if option -n exist - argv[2] = cmd->option
    {
        printNewline = 0;
        //i = 3;
    }
	i = 1;
    while (data[i]) 
    {
        printf("%s", data[i]);
        // if (i < argc - 1)
        //     printf(" ");
        i++;
    } 
    if (printNewline)
        printf("\n");
    return 0;
}