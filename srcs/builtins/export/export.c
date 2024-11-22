/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:48:51 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/22 12:21:19 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
    while (env_export_sorted[i] && env_export_sorted[i+1])
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

char *ft_magouilles(t_env *head)
{
    t_env *temp;
    char *str1;
    char *str2;

    temp = head;
    str1 = ft_strjoin(temp->name, "=");
    str2 = ft_strjoin(str1, temp->value);
    free(str1);
    return (str2);
}

char **env_to_export(t_env *env_list)
{
    char **env_export;
    int len;
    int i;
    t_env *temp;

    temp = env_list;
    i = 0;
    len = cmb_env(temp);
    env_export = (char **)malloc(sizeof(char *) * (len + 1));
    if (!env_export)
        return (NULL);
    while (temp)
    {
        env_export[i] = ft_magouilles(temp);
        temp = temp->next;
        i++;
    }
    env_export[i] = NULL;
    return (sort_env_export(env_export));
}

void free_export_content(t_export *export) {
    if (export && export->content) {
        free_tabtab(export->content);
        export->content = NULL;
    }
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

char **replace_export(char **env_export, char **split_arg)
{
    int i = 0;
    
    while (env_export[i])
    {
        if (ft_strncmp(env_export[i], split_arg[0], ft_strlen(split_arg[0])) == 0)
        {
            free(env_export[i]);
            env_export[i] = ft_strjoin(split_arg[0], ft_strjoin("=", split_arg[1]));
            free(split_arg[0]);
            free(split_arg[1]);
            return (env_export);
        }
        i++;
    }
    free(split_arg[0]);
    free(split_arg[1]);
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

char **append_to_export(char **env_export, char *arg)
{
    char **temp;
    int i;

    // Créer un tableau temporaire avec une taille augmentée de 1.
    i = 0;
    while (env_export[i])
        i++;
    temp = (char **)malloc(sizeof(char *) * (i + 2));
    if (!temp)
        return (NULL);

    // Copier l'ancien tableau dans le nouveau.
    for (i = 0; env_export[i]; i++)
        temp[i] = ft_strdup(env_export[i]);

    // Ajouter l'élément supplémentaire.
    temp[i] = ft_strdup(arg);
    temp[i + 1] = NULL;

    // Libérer l'ancien tableau et le remplacer par le nouveau.
    free_tabtab(env_export);
    return sort_env_export(temp);
}


void printf_export(char **env_export)
{
    int is_open_quote;
    int i;
    int j;

    i = 0;
    j = 0;
    is_open_quote = 0;
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

    if (!name || !envlist)
        return NULL;
    if (check_equal_arg(name) == 1)
        split_name = ft_split(name, '=');
    else
        split_name = ft_split(name, ' ');
    if (!split_name || !split_name[0])
        return NULL;
    temp = envlist;
    value = return_env_value(temp, split_name[0]);
    free_tabtab(split_name);
    return value;
}

t_export *get_export(void)
{
    static t_export export;
    return (&export);
}

int verif_if_in_export(char **export, char *arg)
{
    int i;
    char **split_arg;
    int is_equal;

    i = 0;
    is_equal = 0;
    split_arg = NULL;
    if (!export)
        return 0;
    while (arg[i])
    {
        if (arg[i] == '=')
            is_equal = 1;
        i++;
    }
    if (is_equal == 1)
        split_arg = ft_split(arg, '=');
    i = 0;
    while (export[i])
    {
        if (split_arg != NULL)
        {
            if (ft_strncmp(export[i], split_arg[0], ft_strlen(split_arg[0])) == 0)
            {
                free_tabtab(split_arg);
                return 1;
            }
        }
        else if (ft_strncmp(export[i], arg, ft_strlen(arg)) == 0)
            return (1);
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
    free_tabtab(split_arg);
    return export;
}

int len_before_space(char *arg)
{
    int len;

    len = 0;
    while (arg[len] && arg[len] != '=')
        len++;
    return (len);
}

void init_export(t_export *export_list, t_env *envlist)
{
    if (!export_list->content)
        export_list->content = env_to_export(envlist);
}
int is_env_name_valid(char *name)
{
    int i;

    i = 0;
    if (name[0] >= '0' && name[0] <= '9')
        return 1;
    while (name[i])
    {
        if (name[i] == '=')
        {
            if (name[i + 1] == '\0') //! TEMPORAIRE
                return 1;            //! JUSTE POUR EVITER LE SEGFAULT
            return 0;
        }
        if ((name[i] >= 32 && name[i] < 48) || (name[i] >= 58 && name[i] < 65) || (name[i] >= 91 && name[i] < 95) || name[i] == 96 || name[i] >= 123)
            return 1;
        i++;
    }
    return 0;
}

void replace_env_value(t_env **env_list, char **arg)
{
    t_env **temp;

    if (*env_list == NULL || env_list == NULL)
        return;
    temp = env_list;
    while (*temp)
	{
		if (ft_strcmp((*temp)->name, arg[0]) == 0)
		{
            free((*temp)->value);
            (*temp)->value = ft_strdup(arg[1]);
            return;
		}
		*temp = (*temp)->next;
	}
}

void export_to_env(t_env **env_list, char **arg)
{
    t_env *new;
    t_env **tmp;

    new = (t_env *)malloc(sizeof(t_env));
    if (!new)
        return;
    new->name = ft_strdup(arg[0]);
    new->value = ft_strdup(arg[1]);
    new->next = NULL;
    if (*env_list == NULL)
    {
        *env_list = new;
        return;
    }
    tmp = env_list;
    while ((*tmp)->next)
        *tmp = (*tmp)->next;
    (*tmp)->next = new;
    env_list = tmp;
}

void ft_export(t_env *env_list, char *arg)
{
    t_export *export = get_export();
    char **split_arg;
    char *env_value = NULL;

    init_export(export, env_list);
    if (!export->content)
        return;
    env_value = pipeline_to_env_value(env_list, arg);
    split_arg = NULL;
    if (!arg)
        printf_export(export->content);
    else if (is_env_name_valid(arg) == 1)
        printf("bash: export: `%s': not a valid identifier\n", arg);
    else if (check_equal_arg(arg) == 1)
    {
        split_arg = ft_split(arg, '=');
        if (env_value == NULL)
        {
            if (verif_if_in_export(export->content, arg) == 1)
                export->content = replace_one_in_export(export->content, arg);
            else
                export->content = append_to_export(export->content, arg);
            export_to_env(&env_list, split_arg);
        }
        else
        {
            export->content = replace_export(export->content, split_arg);
            if (strcmp(env_value, split_arg[1]) != 0)
                replace_env_value(&env_list, split_arg);
        }
        free_tabtab(split_arg);
    }
    else if ((check_equal_arg(arg) == 0 || check_equal_arg(arg) == 2) && env_value == NULL)
        export->content = append_to_export(export->content, arg);
}
