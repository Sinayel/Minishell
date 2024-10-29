/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:21:59 by ylouvel           #+#    #+#             */
/*   Updated: 2024/10/29 21:21:35 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//5 Fonction pour verifier si c'est une cmd ou un argument
t_token *cmd_token(t_token *list)
{
    t_token *tmp = list;
    tmp->type = CMD;
    tmp = tmp->next;
    while(tmp != NULL)
    {
        if(tmp->prev->type == PIPE && tmp->type == ARG)
            tmp->type = CMD;
        else if (tmp->type != PIPE && tmp->type >= PIPE)
            tmp->type = ARG;
        tmp = tmp->next;
    }
    return list;
}

t_token *id_token(t_token *list)
{
    t_token *tmp = list;
    t_token *tmp2 = list;
    while (tmp != NULL)
    {
        if (strcmp(tmp->token, "|") == 0)
            tmp->type = PIPE;
        else if (strcmp(tmp->token, ">>") == 0)
            tmp->type = APPEND;
        else if (strcmp(tmp->token, "<<") == 0)
            tmp->type = HEREDOC;
        else if (strcmp(tmp->token, ">") == 0)
            tmp->type = TRUNC;
        else if (strcmp(tmp->token, "<") == 0)
            tmp->type = INPUT;
        else
            tmp->type = ARG;
        tmp = tmp->next;
    }
    tmp2 = cmd_token(tmp2);
    return list;
}
