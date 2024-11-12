/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:58:53 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/08 12:06:34 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_free_path(t_path *path)
{
    t_path *temp;
    if(!path)
        return ;

    while (path)
    {
        temp = path->next;
        free(path->name);
        free(path);
        path = temp;
    }
    path = NULL;
}
