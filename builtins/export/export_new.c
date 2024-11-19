/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:46:03 by judenis           #+#    #+#             */
/*   Updated: 2024/11/19 15:15:37 by judenis          ###   ########.fr       */
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
            if (temp->value)
                env_export[i] = ft_strjoin(temp->name, temp->value);
            else
                env_export[i] = ft_strjoin(temp->name, ft_strjoin("=", temp->value));
            i++;
        }
        temp = temp->next;
    }
    env_export[i] = NULL;
    return (env_export);
}
// return 1 ou 2 lorsqu'un espace est trouve
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

char **sort_env_export(char **env_export)
{
    int i;
    char *temp;
    char **env_export_sorted;
    i = 0;
    temp = NULL;
    if (env_export == NULL)
        return NULL;
    env_export_sorted = env_export;
    while (env_export_sorted && env_export_sorted[i] && env_export_sorted[i+1])
    {
        if (ft_strcmp(env_export_sorted[i], env_export_sorted[i+1]) > 0)
        {
            temp = env_export_sorted[i];
            env_export_sorted[i] = env_export_sorted[i+1];
            env_export_sorted[i+1] = temp;
            i = 0;
        }
        else
            i++;
    }
    return env_export_sorted;
}

void printf_export(char **env_export)
{
    char **env_export_sorted;
    int is_open_quote;
    int i;
    int j;

    i = 0;
    j = 0;
    is_open_quote = 0;
    env_export_sorted = sort_env_export(env_export);
    if (!env_export || !env_export[0])
        return;
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
    free_tabtab(env_export_sorted);
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

t_export *get_export(t_env *envlist)
{
    static t_export export;
    if (!export.content)
        export.content = env_to_export(envlist);
    return (&export);
}

int verif_if_in_export(char **export, char *arg)
{
    int i;
    char **split_arg;

    i = 0;
    split_arg = ft_split(arg, '=');
    while (export[i])
    {
        if (ft_strncmp(export[i], split_arg[0], ft_strlen(split_arg[0])) == 0)
        {
            free_tabtab(split_arg);
            return 1;
        }
        i++;
    }
    return 0;
}

char **replace_one_in_export(char **export, char *arg)
{
    int i;
    char **split_arg;

    i = 0;
    split_arg = ft_split(arg, '=');
    while (export[i])
    {
        if (ft_strncmp(export[i], split_arg[0], ft_strlen(split_arg[0])) == 0)
        {
            free(export[i]);
            export[i] = ft_strdup(arg);
        }
        i++;
    }
    return export;
}

void ft_export(t_env *env_list, char *arg)
{
    t_export *export = get_export(env_list);
    char **split_arg;
    char *env_value = NULL;

    env_value = pipeline_to_env_value(env_list, arg);
    split_arg = NULL;
    if (!arg)
        printf_export(export->content);
    else if (verif_if_in_export(export->content, arg) == 1 && (check_equal_arg(arg) == 1 || check_equal_arg(arg) == 2))
        replace_one_in_export(export->content, arg);
    else if ((check_equal_arg(arg) == 0 || check_equal_arg(arg) == 2) && is_env_name_valid(arg) == 0 && env_value == NULL && verif_if_in_export(export->content, arg) == 0)
        export->content = append_to_export(export->content, arg);
    else if ((check_equal_arg(arg) == 0 || check_equal_arg(arg) == 2) && is_env_name_valid(arg) == 0 && env_value != NULL)
        return;
    else if (check_equal_arg(arg) == 1 && is_env_name_valid(arg) == 0 && env_value == NULL)
    {
        split_arg = ft_split(arg, '=');
        export->content = append_to_export(export->content, arg);
        export_to_env(&env_list, split_arg);
        free_tabtab(split_arg);
    }
    else if (check_equal_arg(arg) == 1 && is_env_name_valid(arg) == 0 && env_value != NULL)
    {
        split_arg = ft_split(arg, '=');
        export->content = replace_export(export->content, split_arg);
        replace_env_value(&env_list, split_arg);
        free_tabtab(split_arg);
    }
    else
        printf("bash: export: `%s': not a valid identifier\n", arg);
}
