#include "minishell.h"

// void *custom_realloc(void *ptr, size_t new_size) 
// {
//     if (ptr == NULL) {
//         return malloc(new_size);
//     }
    
//     if (new_size == 0) {
//         free(ptr);
//         return NULL;
//     }

//     void *new_ptr = malloc(new_size);
    
//     if (new_ptr == NULL)
//         return NULL;
//     // Copy the data from the old block to the new block.
//     // Copy at most the minimum of the old size and the new size.
//     size_t old_size = malloc_usable_size(ptr); // Get the size of the old block
//     size_t copy_size = (new_size < old_size) ? new_size : old_size;
    
//     memcpy(new_ptr, ptr, copy_size);
    
//     // Free the old block.
//     free(ptr);
    
//     return new_ptr;
// }

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

void find_usd(char **data,  t_env *env)
{
    int i;
    char *start;
    char *val;
    size_t len;
    char *key;
 
    i = 1;
    while (data[i])
    {   
        key = ft_strjoin(data[i], "=");
        len = ft_strlen(key);
        start = ft_strchr(key, '$');
        if (start != NULL && len > 1)
        {
            start++;
            val = search_value(start, env);
            free(key);
            free(data[i]);
            data[i] = ft_strdup(val);
        }
        i++;
    }
}