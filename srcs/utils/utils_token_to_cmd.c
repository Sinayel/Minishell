/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token_to_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 15:06:56 by ylouvel           #+#    #+#             */
/*   Updated: 2024/12/15 15:07:57 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*skip_redirection(t_token *tmp)
{
	if (tmp->next && tmp->next->type == ARG)
		tmp = tmp->next;
	return (tmp->next);
}

void	free_args_and_cmd(t_cmd *cmd, int i)
{
	while (i > 0)
		free(cmd->cmd_arg[--i]);
	free(cmd->cmd_arg);
	free(cmd);
}

t_cmd	*cleanup_and_return_null(t_cmd *cmd_head)
{
	if (cmd_head)
		free_cmd();
	return (NULL);
}

void	initialize_cmd_files(t_cmd *cmd)
{
	cmd->infile = -2;
	cmd->outfile = -2;
}

void	append_cmd(t_cmd **cmd_head, t_cmd **cmd_tail, t_cmd *new_cmd)
{
	if (!*cmd_head)
		*cmd_head = new_cmd;
	else
		(*cmd_tail)->next = new_cmd;
	*cmd_tail = new_cmd;
}
