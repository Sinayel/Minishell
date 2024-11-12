/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:22:36 by judenis           #+#    #+#             */
/*   Updated: 2024/11/12 16:10:59 by judenis          ###   ########.fr       */
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

void export_to_env(t_env **env_list, char **arg)
{
    t_env *new;
    t_env **tmp;

    if (*env_list == NULL)
        return;
    // printf("name = %s, value = %s", split_arg[0], split_arg[1]);
    new = (t_env *)malloc(sizeof(t_env));
    if (!new)
        return;
    new->name = arg[0];
    new->value = arg[1];
    new->next = NULL;
    tmp = env_list;
    while ((*tmp)->next)
        *tmp = (*tmp)->next;
    (*tmp)->next = new;
    env_list = tmp;
}

void ft_export(t_env *env_list, char *arg)
{
    char **split_arg;

    if (arg == NULL)
        print_env_export(env_list);
    else
    {
        split_arg = ft_split(arg, '=');
        if (return_env_value(env_list, split_arg[0]) != NULL)
            replace_env_value(&env_list, split_arg);
        else
            export_to_env(&env_list, split_arg);
    }
}

// void print_env_export(t_env *head)
// {
//     t_env *temp;
//     char *alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
//     int i;

//     i = 0;

//     if (head == NULL)
//         return;
//     while (i < (int)strlen(alphabet))
//     {
//         temp = head;
//         while (temp != NULL)
//         {
//             if (temp->name[0] == alphabet[i])
//             {
//                 printf("export %s=%s\n", temp->name, temp->value);
//             }
//             temp = temp->next;
//         }
//         i++;
//     }
// }
