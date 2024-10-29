/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipest.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:08:34 by judenis           #+#    #+#             */
/*   Updated: 2024/10/29 18:23:03 by judenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	pipex(t_token *list, char **env)
{
    int	fd_in;
    int	fd_out;

    while (list)
    {
        if (list->type == 1) // INPUT
        {
            fd_in = open_file(list->next->token, 0);
            list = list->next->next;
        }
        else if (list->type == 2) // HEREDOC
        {
            here_doc(list->next->token, env);
            list = list->next->next;
        }
        else if (list->type == 3) // TRUNC
        {
            fd_out = open_file(list->next->token, 1);
            list = list->next->next;
        }
        else if (list->type == 4) // APPEND
        {
            fd_out = open_file(list->next->token, 2);
            list = list->next->next;
        }
        else if (list->type == 5) // PIPE
        {
            do_pipe(list->next->token, env);
            list = list->next->next;
        }
        else if (list->type == 6) // CMD
        {
            do_pipe(list->token, env);
            list = list->next;
        }
        else if (list->type == 7) // ARG
        {
            do_pipe(list->token, env);
            list = list->next;
        }
    }
}

int main(int ac, char **av, char **env) 
{
    (void)ac;
    (void)av;
    t_token *list;
    list = (t_token)malloc(sizeof(t_token));
    list->token = "cat";
    list->type = 6;
    list->i = 0;
    list = list->next;
    list->token = "Makefile";
    list->type = 7;
    list->i = 1;
    list = list->next;
    list->token = "|";
    list->type = 5;
    list->i = 2;
    list = list->next;
    list->token = "grep";
    list->type = 6;
    list->i = 3;
    list = list->next;
    list->token = "=";
    list->type = 7;
    list->i = 4;
    list->next = NULL;
    pipex(list, env);    
}