/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:43:50 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/19 13:42:04 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void echo(t_token *list)
{
    t_token *tmp = list;
    tmp = tmp->next;
    tmp = remove_quote(tmp);
    while(tmp && tmp->type == ARG)
    {
        if(tmp->type == ARG)
            printf("%s", tmp->token);
        if(tmp->next)
            printf(" ");
        tmp = tmp->next;
    }
    printf("\n");
}