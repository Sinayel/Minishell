/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:30:24 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/06 19:34:36 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_type(t_token *list)
{
	t_token	*tmp;

	tmp = list;
	if ((tmp->type == PIPE && tmp->next->type == PIPE) || (tmp->first == 1
			&& ft_strcmp(tmp->token, "|") == 0))
	{
		msg_error(2);
		return (1);
	}
	return (0);
}

int	check_pipe(t_token *list)
{
	t_token	*tmp;

	tmp = list;
	if (ft_strcmp(tmp->token, "|") == 0)
	{
		msg_error(2);
		return (1);
	}
	while (tmp)
	{
		if ((tmp->next == NULL && tmp->type == PIPE) || (tmp->type == PIPE
				&& (tmp->next->type == TRUNC || tmp->next->type == APPEND
					|| tmp->next->type == INPUT)))
		{
			msg_error(2);
			return (1);
		}
		if (tmp->next != NULL)
		{
			if (check_type(tmp) == 1)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	check_redirection(t_token *list)
{
	t_token	*tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->type == TRUNC || tmp->type == APPEND || tmp->type == INPUT
			|| tmp->type == HEREDOC)
		{
			if (tmp->next == NULL || tmp->next->type == PIPE)
			{
				msg_error(1);
				return (1);
			}
			if (tmp->next->type == TRUNC || tmp->next->type == APPEND
				|| tmp->next->type == INPUT || tmp->next->type == HEREDOC)
			{
				msg_error(1);
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

char	*check_quote(t_token *tmp, int *i, int *j)
{
	while (tmp->token[*i])
	{
		if (tmp->token[*i] == '\"')
		{
			(*i)++;
			continue ;
		}
		if (tmp->token[*i] != '\"')
		{
			tmp->token[*j] = tmp->token[*i];
			(*i)++;
			(*j)++;
		}
	}
	tmp->token[*j] = '\0';
	*i = 0;
	*j = 0;
	return (tmp->token);
}
