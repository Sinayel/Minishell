/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:43:50 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/25 15:33:11 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int echo(t_token *list)
{
    t_token *tmp = list;
    while(tmp)
    {
        if(ft_strcmp(tmp->token, "echo") == 0)
            break;
        tmp = tmp->next;
    }
    if(tmp->next)
        tmp = tmp->next;
    while(tmp && tmp->type == ARG)
    {
        if(tmp->type == ARG)
            printf("%s", tmp->token);
        if(tmp->next)
            printf(" ");
        tmp = tmp->next;
    }
    printf("\n");
    return (0);
}
