/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_echo.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ssemanco <ssemanco@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/03 11:06:15 by ssemanco      #+#    #+#                 */
/*   Updated: 2023/06/03 11:28:45 by ssemanco      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int cmd_echo(int argc, char **argv)
{
    int printNewline = 1;
    int i;

    i = 2;
    if (argc > 1 && strcmp(argv[2], "-n") == 0) //if option -n exist
    {
        printNewline = 0;
        argc--;
        i = 3;
    }
    while (i < argc) 
    {
        printf("%s", argv[i]);
        if (i < argc - 1)
            printf(" ");
        i++;
    } 
    if (printNewline)
        printf("\n");
    return 0;
}