#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_data
{
    char **env;
    char *input;
} t_data;

t_data *get_data(void)
{
    static t_data data;
    return (&data);
}

char *get_env(const char *var, char **env)
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

void msg_dollar(const char *before, const char *env_var)
{
    t_data *data = get_data();
    char *env_value = get_env(env_var, data->env);

    if (before)
        printf("%s", before);
    
    if (env_value)
        printf("%s", env_value);
    else
        printf("$%s", env_var);
}

char *dollar_check(char **before, char **env_var)
{
    t_data *data = get_data();
    
    if (data->input == NULL)
        return NULL;

    char *dollar_pos = strchr(data->input, '$');
    
    if (dollar_pos != NULL)
    {
        *before = strndup(data->input, dollar_pos - data->input);
        *env_var = strdup(dollar_pos + 1);
        
        return *env_var;
    }
    return NULL;
}

int main(int argc, char **argv, char **env)
{
    t_data *data = get_data();
    data->input = strdup("USER$USER");  // Exemple de chaîne

    data->env = env;  // Associe l'environnement à data->env

    char *before = NULL;
    char *env_var = NULL;

    // Appel de dollar_check pour séparer la chaîne
    if (dollar_check(&before, &env_var) != NULL)
    {
        msg_dollar(before, env_var);  // Affiche la chaîne formatée
    }
    else
    {
        printf("Pas de variable d'environnement trouvée.\n");
    }

    // Libère la mémoire
    free(data->input);
    free(before);
    free(env_var);

    return 0;
}
