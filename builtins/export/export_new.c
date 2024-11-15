/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:46:03 by judenis           #+#    #+#             */
/*   Updated: 2024/11/15 13:20:47 by judenis          ###   ########.fr       */
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
    }
    return (len);
}

static char **env_to_export(t_env *env_list)
{
    char **env_export;
    int len;
    int i;
    t_env *temp;

    len = cmb_env(env_list);
    env_export = (char **)malloc(sizeof(char *) * (len + 1));
    if (!env_export)
        return (NULL);
    i = 0;
    temp = env_list;
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
    while (arg[i])
    {
        if (arg[i] == '=' && arg[i + 1] != '\0')
            return 1;
        if (arg[i] == '=' && arg[i + 1] == '\0')
            return 2;
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
    temp = (char **)malloc(sizeof(char *) * (cmb_export(env_export) + 1));
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

void ft_export(t_env **env_list, char *arg)
{
    char **env_export;
    char **split_arg;

    env_export = env_to_export(*env_list);
    int i =0;
    int j = 0;
    split_arg= NULL;
    if (!arg)
    {
        while (env_export[i])
        {
            j = 0;
            while (env_export[i][j])
            {
                if (env_export[i][j] == '=')
                    printf("\"");
                printf("%c", env_export[i][j]);
                if (env_export[i][j+1] == '\n')
                    printf("\"");
                j++;
            }
            i++;
        }
    }
    else if ((check_equal_arg(arg) == 0 || check_equal_arg(arg) == 2) && is_env_name_valid(arg) == 0 && return_env_value(*env_list, split_arg[0]) == NULL)
    {
        env_export = append_to_export(env_export, arg);
    }
    else if ((check_equal_arg(arg) == 0 || check_equal_arg(arg) == 2) && is_env_name_valid(arg) == 0 && return_env_value(*env_list, split_arg[0]) != NULL)
        return;
    else if (check_equal_arg(arg) == 1 && is_env_name_valid(arg) == 0 && return_env_value(*env_list, split_arg[0]) == NULL)
    {
        split_arg = ft_split(arg, '=');
        env_export = append_to_export(env_export, arg);
        export_to_env(env_list, split_arg);
        free_tabtab(split_arg);
    }
    else if (check_equal_arg(arg) == 1 && is_env_name_valid(arg) == 0 && return_env_value(*env_list, split_arg[0]) != NULL)
    {
        split_arg = ft_split(arg, '=');
        env_export = replace_export(env_export, split_arg);
        replace_env_value(env_list, split_arg);
        free_tabtab(split_arg);
    }
    else
        printf("bash: export: `%s': not a valid identifier\n", arg);
}
