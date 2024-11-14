/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:08:54 by judenis           #+#    #+#             */
/*   Updated: 2024/11/14 17:50:34 by judenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../env/env.h"

void ft_unset(t_env **env_list, char *arg)
{
    t_env *temp;
    t_env *prev;

    temp = *env_list;
    prev = NULL;
    while (temp)
    {
        if (ft_strcmp(temp->name, arg) == 0)
        {
            if (prev == NULL)
                *env_list = temp->next;
            else
                prev->next = temp->next;
            free(temp->name);
            free(temp->value);
            free(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}
// {
//     t_env **temp;
    
//     temp = env_list;
//     while (ft_strcmp((*temp)->next->name, arg) != 0 && *temp)
//         *temp = (*temp)->next;
//     if ((*temp)->next->name == arg)
//     {
//         free((*temp)->next->name);
//         free((*temp)->next->value);
//         free((*temp)->next);
//         (*temp)->next = (*temp)->next->next;
//     }
//     else
//         printf("bash: unset: %s: not found\n", arg);
// }