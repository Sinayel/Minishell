#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_env_var(const char *var, char **env)
{
    int i = 0;
    size_t len = strlen(var);

    while (env[i])
    {
        if (strncmp(env[i], var, len) == 0 && env[i][len] == '=')
        {
            return env[i] + len + 1;
        }
        i++;
    }
    return NULL;
}

int main(int argc, char **argv, char **env)
{
    char *user = get_env_var(argv[1], env);
    
    if (user)
        printf("Valeur de USER: %s\n", user);
    else
        printf("Variable USER non trouvée.\n");

    return 0;
}
