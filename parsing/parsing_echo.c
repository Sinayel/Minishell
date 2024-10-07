#include "../utils/utils.c"

void print_string(char *str[], int argc)
{
    int i = 2;
    int j = 0;

    while (str[i])
    {
        j = 0;
        while (str[i][j])
        {
            write(1, &str[i][j], 1);
            j++;
        }
        if (argc > 3 && str[i][j] == '\0' && i != argc - 1)
        {
            write(1, " ", 1);
        }
        i++;
    }
}

int echo(char *str[], int argc)
{
    if (ft_strcmp(str[1], "echo") == 0 && str[2] == NULL)
    {
        printf("echo\n");
        return 0;
    }
    else if (ft_strcmp(str[2], "-n") == 0 && str[3] != NULL)
        printf("%sMINISHELL$ ", str[3]);
    else if (ft_strcmp(str[2], "-n") != 0 && str[2] != NULL)
    {
        print_string(str, argc);
        printf("\n");
    }
    return 0;
}