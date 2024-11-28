/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:07:14 by judenis           #+#    #+#             */
/*   Updated: 2024/11/28 17:25:27 by judenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int len_cmdblocks(t_token *list)
{
    t_token *tmp;
    int i;

    i = 0;
    tmp = list;
    while (tmp)
    {
        if (tmp->type == CMD)
            i++;
        tmp = tmp->next;
    }
    return (i);
}

int len_in_block(t_token *list)
{
    int len;

    len = 0;
    while (list && (list->type == CMD || list->type == ARG))
    {
        len++;
        list = list->next;
    }
    return (len);
}

bool is_builtin(char *str)
{
    if (ft_strcmp(str, "cd") || ft_strcmp(str, "pwd") == 0 || ft_strcmp(str, "unset") == 0 || ft_strcmp(str, "env") == 0 || ft_strcmp(str, "echo") == 0 || ft_strcmp(str, "exit") == 0 || ft_strcmp(str, "export") == 0)
		return true;
    return false;
}

void print_cmd(t_cmd *list)
{
    t_cmd *tmp;

    tmp = list;
    int i = 0;
    int len = 0;
    while (tmp)
    {
        i = 0;
        while (tmp->cmd_arg[i])
        {
            printf("noeud n.%d = [%s]\n", len, tmp->cmd_arg[i]);
            i++;
        }
        len++;
        tmp = tmp->next;
    }
}

t_cmd *token_to_cmd(t_token *list)
{
    t_token *tmp = list;
    t_cmd *cmd_head = NULL;
    t_cmd *cmd_tail = NULL;
    int i;

    while (tmp)
    {
        if (tmp->type == CMD)
        {
            // Création d'un nouveau nœud de commande
            t_cmd *new_cmd = malloc(sizeof(t_cmd));
            if (!new_cmd)
                return (NULL); // Gestion des erreurs d'allocation mémoire
            new_cmd->next = NULL;

            // Comptage des arguments nécessaires
            int arg_count = len_in_block(tmp);

            // Allocation pour les arguments (commande incluse)
            new_cmd->cmd_arg = malloc(sizeof(char *) * (arg_count + 1));
            if (!new_cmd->cmd_arg)
            {
                free(new_cmd);
                return (NULL);
            }

            // Copie de la commande et des arguments
            i = 0;
            while (tmp && (tmp->type == CMD || tmp->type == ARG))
            {
                new_cmd->cmd_arg[i] = ft_strdup(tmp->token);
                if (!new_cmd->cmd_arg[i])
                {
                    // Libération en cas d'échec
                    while (i > 0)
                        free(new_cmd->cmd_arg[--i]);
                    free(new_cmd->cmd_arg);
                    free(new_cmd);
                    return (NULL);
                }
                tmp = tmp->next;
                i++;
            }
            new_cmd->cmd_arg[i] = NULL;

            // Ajout à la liste chaînée des commandes
            if (!cmd_head)
                cmd_head = new_cmd;
            else
                cmd_tail->next = new_cmd;
            cmd_tail = new_cmd;
        }
        else
            tmp = tmp->next;
    }

    return (cmd_head);
}

int exec_not_builtin(t_cmd *list)
{
    t_cmd *tmp;

    tmp = list;
    while (tmp)
    {
        if (is_builtin(tmp->cmd_arg[0]) == false)
        {
            
        }
    }
}

