#include "includes.h"

int ft_sig_handler(int sig, int raf)
{
    (void)raf;
    if (sig == SIGINT)
        exit(0);
}

int ft_strchr(char *str, char *to_find)
{
    int i;
    int j;

    i = 0;
    while (str[i])
    {
        if (str[i] == to_find[0])
        {
            j = 0;
            while (str[i] == to_find[j])
            {
                i++;
                j++;
            }
            if (to_find[j] == '\0')
                return (0);
        }
        i++;
    }
    return (0);
}

// int ft_pwd(char **env)
// {
    
// }

int main()
{
    char *input;
    signal(SIGINT, ft_sig_handler)
    while (1)
    {
        input = readline("Minishell$");
        if (*input)
            add_history(input);
        if (ft_strchr(input, "pwd") == 1)
            printf("%s\n", input);
        free(input);
    }
}