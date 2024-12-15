/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:39:24 by ylouvel           #+#    #+#             */
/*   Updated: 2024/12/15 17:39:35 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_cmd(void)
{
	t_data	*data;
	t_cmd	**list;
	t_cmd	*tmp;
	t_cmd	*current;
	int		len;

	data = get_data();
	list = &data->cmd;
	if (list == NULL || *list == NULL)
		return ;
	len = len_cmd(*list) - 1;
	current = *list;
	while (current && len--)
	{
		tmp = current;
		current = current->next;
		free_cmd_vars(tmp);
	}
	free_cmd_vars(current);
	*list = NULL;
}

int	len_cmd(t_cmd *list)
{
	int		len;
	t_cmd	*tmp;

	len = 0;
	if (!list)
		return (0);
	tmp = list;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

int	len_cmdblocks(t_token *list)
{
	t_token	*tmp;
	int		i;

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

int	len_in_block(t_token *list)
{
	int	len;

	len = 0;
	while (list)
	{
		if (list->type == INPUT || list->type == HEREDOC || list->type == APPEND
			|| list->type == TRUNC)
		{
			if (list->next->type == ARG)
				list = list->next;
			list = list->next;
			continue ;
		}
		if (list->type == PIPE)
			break ;
		len++;
		list = list->next;
	}
	return (len);
}

bool	is_builtin(char *str)
{
	if (ft_strcmp(str, "cd") == 0 || ft_strcmp(str, "pwd") == 0
		|| ft_strcmp(str, "unset") == 0 || ft_strcmp(str, "env") == 0
		|| ft_strcmp(str, "echo") == 0 || ft_strcmp(str, "exit") == 0
		|| ft_strcmp(str, "export") == 0)
		return (true);
	return (false);
}
