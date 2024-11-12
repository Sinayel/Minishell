/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:22:36 by judenis           #+#    #+#             */
/*   Updated: 2024/11/12 14:53:19 by judenis          ###   ########.fr       */
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

void export_to_env(t_env **env_list, char *arg)
{
    t_env *new;
    t_env **tmp;
    char **split_arg;

    if (*env_list == NULL)
        return;
    split_arg = ft_split(arg, '=');
    new = (t_env *)malloc(sizeof(t_env));
    if (!new)
        return;
    new->name = split_arg[0];
    new->value = split_arg[1];
    new->next = NULL;
    tmp = env_list;
    while ((*tmp)->next)
        *tmp = (*tmp)->next;
    (*tmp)->next = new;
    env_list = tmp;
}

void ft_export(t_env *env_list, char *arg)
{
    printf("test\n");
    if (arg == NULL)
        print_env_export(env_list);
    else
    {
        export_to_env(&env_list, arg);
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
