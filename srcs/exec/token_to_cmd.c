/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 15:05:26 by ylouvel           #+#    #+#             */
/*   Updated: 2024/12/15 15:09:13 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*create_new_cmd(void)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->next = NULL;
	return (new_cmd);
}

int	duplicate_and_store_arg(t_cmd *new_cmd, t_token **tmp, int *i,
		t_cmd *cmd_head)
{
	new_cmd->cmd_arg[*i] = ft_strdup((*tmp)->token);
	if (!new_cmd->cmd_arg[*i])
	{
		free_args_and_cmd(new_cmd, *i);
		cleanup_and_return_null(cmd_head);
		return (0);
	}
	*tmp = (*tmp)->next;
	(*i)++;
	return (1);
}

int	fill_cmd_args(t_cmd *new_cmd, t_token **tmp, t_cmd *cmd_head)
{
	int	i;

	i = 0;
	while (*tmp)
	{
		if (is_redirection_f((*tmp)->type))
		{
			*tmp = skip_redirection(*tmp);
			continue ;
		}
		if ((*tmp)->type == PIPE)
		{
			*tmp = (*tmp)->next;
			break ;
		}
		if (!duplicate_and_store_arg(new_cmd, tmp, &i, cmd_head))
			return (0);
	}
	new_cmd->cmd_arg[i] = NULL;
	return (1);
}

int	populate_cmd_args(t_cmd *new_cmd, t_token **tmp, t_cmd *cmd_head)
{
	int	arg_count;

	arg_count = len_in_block(*tmp) + 1;
	new_cmd->cmd_arg = malloc(sizeof(char *) * arg_count);
	if (!new_cmd->cmd_arg)
	{
		free(new_cmd);
		cleanup_and_return_null(cmd_head);
		return (0);
	}
	return (fill_cmd_args(new_cmd, tmp, cmd_head));
}

t_cmd	*token_to_cmd(t_token *list)
{
	t_token	*tmp;
	t_cmd	*cmd_head;
	t_cmd	*cmd_tail;
	t_cmd	*new_cmd;

	tmp = list;
	cmd_head = NULL;
	cmd_tail = NULL;
	while (tmp)
	{
		if (tmp->type == CMD)
		{
			new_cmd = create_new_cmd();
			if (!new_cmd)
				return (cleanup_and_return_null(cmd_head));
			if (!populate_cmd_args(new_cmd, &tmp, cmd_head))
				return (NULL);
			initialize_cmd_files(new_cmd);
			append_cmd(&cmd_head, &cmd_tail, new_cmd);
		}
		else
			tmp = tmp->next;
	}
	return (cmd_head);
}
