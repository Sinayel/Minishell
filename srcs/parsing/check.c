/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:30:05 by ylouvel           #+#    #+#             */
/*   Updated: 2024/10/25 21:44:50 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


//5 ------------- Pour check les cmd -------------
int args(char *str)
{
    printf("str = %s\n", str);
    if(strcmp(str, "echo") == 0 ||      //3 Cmd a +1 d'arguments (ou 1 seul)
        strcmp(str, "cd") == 0 ||
        strcmp(str, "export") == 0 ||
        strcmp(str, "unset") == 0)
        return 0;
    else if(strcmp(str, "exit") == 0 || //3 Cmd a 1 arguments (Sans option)
            strcmp(str, "pwd") == 0 ||
            strcmp(str, "env") == 0)
        return 2;
    else
        return 1;
}

int check_cmd(t_data *list)
{
    t_data *temp = list;
    int i = 0;
    while(temp != NULL)
    {
        if(args(temp->value) == 1)
            return 1;
        temp = temp->next;
        i++;
    }
    return 0;
}
