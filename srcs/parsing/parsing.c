/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:14:05 by ylouvel           #+#    #+#             */
/*   Updated: 2024/10/31 17:30:50 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_pipe(t_token *list)
{
	t_token	*tmp;

	tmp = list;
	if (strcmp(tmp->token, "|") == 0)
	{
		ft_putstr_fd("minishell: syntax error unexpected token `|'\n", 2);
		return (1);
	}
	while (tmp)
	{
		if (tmp->next == NULL && tmp->type == PIPE)
		{
			ft_putstr_fd("minishell: syntax error unexpected token `|'\n", 2);
			return (1);
		}
		if (tmp->next != NULL)
		{
			if ((tmp->type == PIPE && tmp->next->type == PIPE)
				|| (tmp->first == 1 && strcmp(tmp->token, "|") == 0))
			{
				ft_putstr_fd("minishell: syntax error unexpected token `|'\n", 2);
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	parsing(t_token *list)
{
	t_token	*tmp;

	tmp = list;
	if (check_pipe(list) == 1)
		return (1);
	// 1 -------------------  Check if there is a redirection  -------------------
	while (tmp)
	{
		if (tmp->type == TRUNC || tmp->type == APPEND || tmp->type == INPUT
			|| tmp->type == HEREDOC)
		{
			if (tmp->next == NULL || tmp->next->type == PIPE)
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
					2);
				return (1);
			}
			if (tmp->next->type == TRUNC || tmp->next->type == APPEND
				|| tmp->next->type == INPUT || tmp->next->type == HEREDOC)
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
					2);
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}
