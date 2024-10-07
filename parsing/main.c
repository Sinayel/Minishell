#include "../includes/include.h"

//! ◦ CD with only a relative or absolute path |  (JULIO)
//! ◦ PWD with no options                      |  (JULIO)
//! ◦ UNSET with no options                    |  (JULIO)
//! ◦ EXPORT with no options                   |  (YANNS)
//! ◦ ENV with no options or arguments         |  (YANNS)
//! ◦ EXIT                                     |  (YANNS)

int parsing(char *str[], int argc)
{
    int i = 1;
    if (str[i])
    {
        if (ft_strcmp(str[1], "echo") == 0)
            echo(str, argc);
        if (ft_strcmp(str[1], "cd") == 0)
            printf("cd\n");
        if (ft_strcmp(str[1], "pwd") == 0)
            printf("pwd\n");
        if (ft_strcmp(str[1], "unset") == 0)
            printf("unset\n");
        if (ft_strcmp(str[1], "env") == 0)
            printf("env\n");
        if (ft_strcmp(str[1], "exit") == 0)
            printf("exit\n");
    }
    return 0;
}

int main(int argc, char *argv[])
{
    parsing(argv, argc);
}