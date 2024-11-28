/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:07:14 by judenis           #+#    #+#             */
/*   Updated: 2024/11/28 14:29:58 by judenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int len_cmdblocks(t_token *list)
{
    t_token *tmp;
    int i;

    i = 0;
    tmp = list;
    while (list)
    {
        if (list->type == CMD)
            i++;
        list = list->next;
    }
    return (i);
}

t_cmd *token_to_cmd(t_token *list)
{
    t_token *tmp;
    t_cmd *cmd;
    int len;
    int i;

    tmp = list;
    cmd = malloc(sizeof(t_cmd));
    len = ;
    i = 0;
    cmd->cmd_arg = malloc(sizeof(char *) * (len + 1));
    while (tmp)
    {
        
        tmp = tmp->next;
    }
    while (i < len)
    {
        
    }
}
