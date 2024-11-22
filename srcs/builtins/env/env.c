/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 20:39:47 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/22 15:11:35 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void env_create_oldpwd(t_env **env_list)
{
    t_env *new;
    char cwd[4096];

    getcwd(cwd, sizeof(cwd));
    new = (t_env *)malloc(sizeof(t_env));
    new->name = ft_strdup("OLDPWD");
    new->value = ft_strdup(cwd);
    new->next = NULL;
    (*env_list)->next = new;
}

t_env *env_create_pwd(t_env **env_list)
{
    t_env *new;
    char cwd[4096];

    getcwd(cwd, sizeof(cwd));
    new = (t_env *)malloc(sizeof(t_env));
    new->name = ft_strdup("PWD");
    new->value = ft_strdup(cwd);
    new->next = NULL;
    *env_list = new;
    return *env_list;
}

void ft_free_env(t_env **lst)
{
    t_env *tmp;

    if (!lst || !*lst)
        return;

    while (*lst)
    {
        tmp = (*lst)->next;
        if ((*lst)->name)
            free((*lst)->name);
        if ((*lst)->value)
            free((*lst)->value);
        
        free(*lst);
        *lst = tmp;
    }
    *lst = NULL;
}

t_env *env_import(char **envp)
{
    t_env *env_list;
    char *env_entry;
    char *delimiter;
    char *name;
    int i;

    i = 0;
    env_list = NULL;
    if (!*envp)
        return (env_create_pwd(&env_list));
    while (envp[i])
    {
        env_entry = envp[i];
        delimiter = ft_strchr(env_entry, '=');

        if (delimiter != NULL)
        {
            *delimiter = '\0';
            name = env_entry;
            append_env_var(&env_list, name, delimiter + 1);
            *delimiter = '=';
            i++;
        }
    }
    return (env_list);
}
