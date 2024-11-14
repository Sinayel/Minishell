/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:22:36 by judenis           #+#    #+#             */
/*   Updated: 2024/11/14 18:47:26 by judenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../env/env.h"


t_env *find_next_alphabetically(t_env *head, t_env *last_printed)
{
    t_env *current = head;
    t_env *smallest = NULL;

    while (current != NULL)
    {
        if ((last_printed == NULL || ft_strcmp(current->name, last_printed->name) > 0) &&
            (smallest == NULL || ft_strcmp(current->name, smallest->name) < 0))
        {
            smallest = current;
        }
        current = current->next;
    }
    return smallest;
}

void print_env_export(t_env *head)
{
    t_env *last_printed = NULL;
    t_env *next;

    while ((next = find_next_alphabetically(head, last_printed)) != NULL)
    {
        if (ft_strcmp(next->name, "_") == 0)
        {
            last_printed = next;
            continue;
        }
        printf("export %s=%s\n", next->name, next->value);
        last_printed = next;
    }
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

int check_equal_arg(char *arg)
{
    int i;

    i = 0;
    while (arg[i])
    {
        if (arg[i] == '=')
            return 1;
        i++;
    }
    return 0;
}

void ft_export(t_env **env_list, char *arg)
{
    char **split_arg;

    if (arg == NULL)
        print_env_export(*env_list);
    // else if (check_equal_arg(arg) == 0)
    else if (!env_list)
    {
        printf("test\n");
        split_arg = ft_split(arg, '=');
        export_to_env(env_list, split_arg);
        free_tabtab(split_arg);
    }
    else if (is_env_name_valid(arg) == 0)
    {
        split_arg = ft_split(arg, '=');
        if (return_env_value(*env_list, split_arg[0]) != NULL)
            replace_env_value(env_list, split_arg);
        else
            export_to_env(env_list, split_arg);
        free_tabtab(split_arg);
    }
    else
        printf("bash: export: `%s': not a valid identifier\n", arg);
}
