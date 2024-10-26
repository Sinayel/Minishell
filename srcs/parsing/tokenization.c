/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:29:09 by ylouvel           #+#    #+#             */
/*   Updated: 2024/10/26 21:10:20 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token *tokenization(char *str)
{
    t_token *list;
    char *tmp;
    list = NULL;
    int i = 0;
    int j = 0;
    while(str[i])
    {
        while (str[i] == 32)
            i++;
        j = i;
        while(str[i] != '<' || str[i] != '>' || str[i] != '|')
            i++;
        if (str[i] == '|' || str[i] == '<' || str[i] == '>')
        {
            i++;
            if ((str[i] == '<' && str[i-1] == '<') || (str[i] == '>' && str[i-1] == '>'))
                i++;
        }
        tmp = ft_substr(str, j, i - j);
        list = add_last(list, tmp);
    }
    return list;
}
