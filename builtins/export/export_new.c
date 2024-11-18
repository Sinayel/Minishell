/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:46:03 by judenis           #+#    #+#             */
/*   Updated: 2024/11/18 18:57:28 by judenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../env/env.h"

int cmb_env(t_env *envlist)
{
    t_env *temp;
    int len;
    
    len = 0;
    temp = envlist;
    while (temp)
    {
        if (temp->name)
            len++;
        temp = temp->next;
    }
    return (len);
}

static char **env_to_export(t_env *env_list)
{
    char **env_export;
    int len;
    int i;
    t_env *temp;

    temp = env_list;
    len = cmb_env(temp);
    env_export = (char **)malloc(sizeof(char *) * (len + 1));
    if (!env_export)
        return (NULL);
    i = 0;
    while (temp)
    {
        if (temp->name)
        {
            env_export[i] = ft_strjoin(temp->name, "=");
            if (temp->value)
                env_export[i] = ft_strjoin(env_export[i], temp->value);
            i++;
        }
        temp = temp->next;
    }
    env_export[i] = NULL;
    return (env_export);
}

int check_equal_arg(char *arg)
{
    int i;

    i = 0;
    if (!arg)
        return 1;
    while (arg[i])
    {
        if (arg[i] == '=' && !arg[i + 1])
            return 2;
        if (arg[i] == '=' && arg[i + 1] != '\0')
            return 1;
        i++;
    }
    return 0;
}

static char **replace_export(char **env_export, char **split_arg)
{
    int i = 0;
    
    while (env_export[i])
    {
        if (ft_strncmp(env_export[i], split_arg[0], ft_strlen(split_arg[0])) == 0)
        {
            free(env_export[i]);
            env_export[i] = ft_strdup(split_arg[0]);
            env_export[i] = ft_strjoin(env_export[i], "=");
            env_export[i] = ft_strjoin(env_export[i], split_arg[1]);
            return (env_export);
        }
        i++;
    }
    return (env_export);
}

int cmb_export(char **env_export)
{
    int i;

    i = 0;
    while (env_export[i])
        i++;
    return (i);
}

static char **append_to_export(char **env_export, char *arg)
{
    char **temp;
    int i;

    i = 0;
    printf("cmb_export(env_export) = %d\n", 50);
    temp = (char **)malloc(sizeof(char *) * (cmb_export(env_export) + 2));
    if (!temp)
        return (NULL);
    while (env_export[i])
    {
        temp[i] = ft_strdup(env_export[i]);
        i++;
    }
    temp[i] = ft_strdup(arg);
    return (temp);
}

void printf_export(char **env_export)
{
    int is_open_quote;
    int i;
    int j;

    char *temp;
    i = 0;
    temp = NULL;
    while (env_export[i] && env_export[i+1])
    {
        if (ft_strcmp(env_export[i], env_export[i+1]) > 0)
        {
            temp = env_export[i];
            env_export[i] = env_export[i+1];
            env_export[i+1] = temp;
            i = 0;
        }
        else
            i++;
    }
    i = 0;
    while (env_export[i])
    {
        is_open_quote = 0;
        j = 0;
        if (env_export[i][0])
            printf("export ");
        while (env_export[i][j])
        {
            // if (env_export[i][0] == '_')
            //     break;
            printf("%c", env_export[i][j]);
            if (env_export[i][j] == '=')
            {
                printf("\"");
                is_open_quote = 1;
            }
            if (!env_export[i][j+1] && is_open_quote == 1)
                printf("\"");
            j++;
        }
        printf("\n");
        i++;
    }
}

char *pipeline_to_env_value(t_env *envlist, char *name)
{
    char *value = NULL;
    char **split_name = NULL;
    t_env *temp;

    if (!name || !envlist) {
        return NULL; // Protection contre les entrées nulles
    }
    if (check_equal_arg(name) == 1)
        split_name = ft_split(name, '=');
    else
        split_name = ft_split(name, ' ');
    if (!split_name || !split_name[0])
    {
        if (split_name) {
            free_tabtab(split_name);
        }
        return NULL;
    }

    temp = envlist;
    value = return_env_value(temp, split_name[0]);
    free_tabtab(split_name);
    return value;
}


// char *pipeline_to_env_value(t_env **envlist, char *name)
// {
//     char *value;
//     char **split_name;
//     t_env *temp;

//     if (check_equal_arg(name) == 1)
//         split_name = ft_split(name, '=');
//     else
//         split_name = ft_split(name, ' ');
//     temp = *envlist;
//     value = return_env_value(temp, split_name[0]);
//     free_tabtab(split_name);
//     return (value);
// }

void ft_export(t_env *env_list, char *arg)
{
    static char **env_export;
    char **split_arg;
    char *env_value = NULL;

    if (!env_export)
        env_export = env_to_export(env_list);
    env_value = pipeline_to_env_value(env_list, arg);
    split_arg = NULL;
    if (!arg)
    {
        printf_export(env_export);
    }
    else if ((check_equal_arg(arg) == 0 || check_equal_arg(arg) == 2) && is_env_name_valid(arg) == 0 && env_value == NULL)
    {
        env_export = append_to_export(env_export, arg);
    }
    else if ((check_equal_arg(arg) == 0 || check_equal_arg(arg) == 2) && is_env_name_valid(arg) == 0 && env_value != NULL)
        return;
    else if (check_equal_arg(arg) == 1 && is_env_name_valid(arg) == 0 && env_value == NULL)
    {
        split_arg = ft_split(arg, '=');
        env_export = append_to_export(env_export, arg);
        export_to_env(&env_list, split_arg);
        free_tabtab(split_arg);
    }
    else if (check_equal_arg(arg) == 1 && is_env_name_valid(arg) == 0 && env_value != NULL)
    {
        split_arg = ft_split(arg, '=');
        env_export = replace_export(env_export, split_arg);
        replace_env_value(&env_list, split_arg);
        free_tabtab(split_arg);
    }
    else
        printf("bash: export: `%s': not a valid identifier\n", arg);
}
