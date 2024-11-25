/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:08:54 by judenis           #+#    #+#             */
/*   Updated: 2024/11/25 17:28:02 by judenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../env/env.h"

t_export *unset_export(t_export *export, char *arg)
{
    int i;
    int j;
    char **dest;

    i = 0;
    j = 0;
    while (export->content[i])
        i++;
    dest = (char **)malloc(sizeof(char *) * (i + 1));
    if (!dest)
        return (NULL);
    i = 0;
    while (export->content[i])
    {
        if (ft_strncmp(export->content[i], arg, ft_strlen(arg)) != 0)
            dest[j++] = ft_strdup(export->content[i]);
        i++;
    }
    free_tabtab(export->content);
    dest[j] = NULL;
    export->content = dest;
    return (export);
}

void ft_unset(t_env **env_list, char *arg)
{
    t_env *temp;
    t_env *prev;
    t_export *export = get_export();
    char **arg_split;
    int i ;

    i = 0;
    if (cmb_word(arg) > 1)
        arg_split = ft_split(arg, ' ');
    else
    {
        arg_split = (char **)malloc(sizeof(char *) * 2);
        arg_split[0] = ft_strdup(arg);
        arg_split[1] = NULL;
    }
    while (arg_split[i])
    {
        export = unset_export(export, arg_split[i]);
        i++;
    }
    i = 0;
    while (arg_split[i]) //! A REVOIR
    {
        temp = *env_list;
        if (!temp)
        {
            free_tabtab(arg_split);
            return;
        }
        prev = NULL;
        while (temp)
        {
            if (ft_strcmp(temp->name, arg_split[i]) == 0)
            {
                if (prev == NULL)
                    *env_list = temp->next;
                else
                    prev->next = temp->next;
                free(temp->name);
                free(temp->value);
                free(temp);
                free_tabtab(arg_split);
                return;
            }
            prev = temp;
            temp = temp->next;
        }
        i++;
    }
    free_tabtab(arg_split);
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