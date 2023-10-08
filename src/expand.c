#include "minishell.h"

char *search_value(char *key, t_env *env)
{
    size_t len;

    len = ft_strlen(key);
    while (env)
    {
        if(ft_strncmp(key, env->key, len) == 0)
            return(env->value);
        env = env->next;
    }
    return (ft_strdup(""));
}

// char* print_qm(char *data, char *prestr)
// {
//     char *subs;
//     char *exitc;
//     size_t len;
    
//     g_exit_status = 666;
//     len = ft_strlen(data);
//     subs = ft_substr(data, ft_strlen(prestr) + 2, len);
//     exitc = ft_itoa(g_exit_status);
//     //printf("SUBSTRING IS %s\n", subs);
//     free(data);
//     data = ft_strjoin(exitc, subs);
//     //printf("DATA IS %s\n", data);
//     printf("%s", prestr);
//     free(subs);
//     free(exitc);
//     return (data);
// }

// void find_usd(char **data,  t_env *env)
// {
//     int i;
//     char *start;
//     char *val;
//     size_t len;
//     char *key;
//     char *prestr;
 
//     i = 1;
//     while (data[i])
//     {   
//         // if(strcmp(data[i], "$?") == 0), '$'
//         // {
//         //     data[i]=print_qm(data[i]);
//         // }   
//             key = ft_strjoin(data[i], "=");
//             len = ft_strlen(key);
//             start = ft_strchr(key, '$');
//             prestr = ft_substr(data[i], 0, len - ft_strlen(start));
//             if (start != NULL && len > 1)
//             {
//                 start++;
//                 if( *start == '?')
//                     data[i]=print_qm(data[i], prestr);
//                 else {
//                 val = search_value(start, env);
//                 free(key);
//                 free(data[i]);
//                 data[i] = ft_strjoin(prestr, val);
//                 free(val);
//                 free(prestr);
//                 }
//             }
//         i++;
//     }
// }

int countUsd(const char *str, char target) {
    int count = 0;

    while (*str != '\0') {
        if (*str == target) {
            count++;
        }
        str++; // Move to the next character in the string
    }

    return count;
}

void find_usd(char **data,  t_env *env)
{
    int i;
    int j;
    char **split;
    char *start;
    char *end;
    char *prestr;
    char *key;
    char *val;
    char  *str1;
    size_t len;

    i = 1;
    while (data[i])
    {   
        if (ft_strchr(data[i], '$') != NULL)
        {
            split = ft_split(data[i], '+');
            if (!split[1])
            {
                len = ft_strlen(split[0]);
                start = ft_strchr(split[0], '$');
                if(len > ft_strlen(start))
                    prestr = ft_substr(split[0], 0, len - ft_strlen(start));
                printf("PRESTRS IS %s\n", prestr);
                j = 0;
                while (j < countUsd(split[0], '$'))
                {
                    start++;
                    end = ft_strchr(start, '$');
                    key = ft_strjoin(ft_substr(start, 0, (ft_strlen(start) - ft_strlen(end))), "=");
                    printf("KEY IS %s\n", key);
                    val = search_value(key, env);
                    str1 = ft_strjoin(prestr, val);
                    printf("FIRST EXPAND  IS %s\n", str1);
                    free(val);
                    free(key);
                    start = end;
                    j++;
                }

            }
            
        }
        i++;   
    }
}