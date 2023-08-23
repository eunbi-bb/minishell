#include "../includes/minishell.h"

void find_usd(char **data)
{
    int i;
    int start;

    i = 0;
    while (data[i])
    {   
        start = ft_strchr(data[i], "$");
        if (start != 0)
        {
            printf("dtat is %s\n", data[i]);
        }
    }
}