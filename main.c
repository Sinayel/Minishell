#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

int main()
{
    char *input;
    while (1)
    {
        input = readline("Minishell$");
        printf("%s\n", input);
        free(input);
    }

}