/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:21:59 by ylouvel           #+#    #+#             */
/*   Updated: 2024/10/28 19:42:42 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//5 Fonction pour verifier si c'est une cmd ou un argument
t_token *cmd_token(t_token *list)
{
    return list;
}

t_token *id_token(t_token *list)
{
    t_token *tmp = list;

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
            tmp = cmd_token(tmp);

        tmp = tmp->next;
    }

    return list;
}
