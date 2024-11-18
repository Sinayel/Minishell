/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:08:54 by judenis           #+#    #+#             */
/*   Updated: 2024/11/18 20:09:26 by judenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../env/env.h"

t_export *unset_export(t_export *export, char *arg)
{
    int i;
    char **dest;

    i = 0;
    dest = (char **)malloc(sizeof(char *) * (cmb_export(export->content) + 1));
    if (!dest)
        return (NULL);
    while (export->content[i])
    {
        if (ft_strncmp(export->content[i], arg, ft_strlen(arg)) == 0)
            i++;
        else
        {
            dest[i] = ft_strdup(export->content[i]);
            i++;
        }
    }
    free_tabtab(export->content);
    dest[i] = NULL;
    export->content = dest;
    free_tabtab(dest);
    return (export);
}

void ft_unset(t_env **env_list, char *arg)
{
    t_env *temp;
    t_env *prev;
    t_export *export = get_export(*env_list);

    temp = *env_list;
    prev = NULL;
    export = unset_export(export, arg);
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