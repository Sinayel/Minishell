/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:21:59 by ylouvel           #+#    #+#             */
/*   Updated: 2024/10/28 18:35:46 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
            tmp->type = CMD; //5 Il faut que je rentre dans un fonction qui check si c'est une comande ou un argument

        tmp = tmp->next;
    }

    return list;
}
