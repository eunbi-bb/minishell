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

char* print_qm(char *data)
{
    char *exitc;
    
    // g_exit_status = 666;
    exitc = ft_itoa(g_exit_status);
    //printf("SUBSTRING IS %s\n", subs);
    free(data);
    data = ft_strdup(exitc);
    //printf("DATA IS %s\n", data);
    free(exitc);
    return (data);
}

void expand(t_tokens *token_list,  t_env *env)
{
	t_tokens *current;
    char *val;
    size_t len;
    char *key;
 
	current = token_list;
    while (current != NULL)
    {   
		if(current->token == QUESTION && current->s_quote == false)
		{
			current->data = print_qm(current->data);
		}
		if(current->token == DOLLAR && current->s_quote == false) 
		{ 
			//printf("DATA IS %s\n", current->data);
            key = ft_strjoin(current->data + 1, "=");
            len = ft_strlen(key);
            if (len > 1)
            {
				//printf("KEY IS  %s\n", key);
                val = search_value(key, env);
                free(key);
				//printf("val is IS  %s\n", val);
				if (val)
				{
					free(current->data);
                	current->data = ft_strdup(val);
					//printf("DATA AFTER  %s\n", current->data);
					//free(val);
				}	
            }
		}
        current = current->next;
    }
}
