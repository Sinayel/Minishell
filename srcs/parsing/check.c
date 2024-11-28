/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:30:24 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/28 16:17:51 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	return_next_next(t_token *tmp)
{
	if (tmp->type == HEREDOC && tmp->next->type == HEREDOC
		&& tmp->next->next->type == HEREDOC)
		return (msg_error(10));
	else if ((tmp->type == TRUNC || tmp->type == APPEND)
		&& (tmp->next->type == HEREDOC && (tmp->next->next->type == INPUT
				|| tmp->next->next->type == HEREDOC)))
		return (msg_error(10));
	else if (tmp->type == HEREDOC && tmp->next->type == HEREDOC
		&& tmp->next->next->type == INPUT)
		return (msg_error(9));
	return (0);
}

int	for_trunc_and_heredoc(t_token *tmp)
{
	if (!tmp->next)
		return (msg_error(1));
	if (tmp->type == TRUNC && tmp->next->type == INPUT)
		return (msg_error(8));
	if (tmp->type == TRUNC && tmp->next->type == HEREDOC)
		return (msg_error(9));
	if ((tmp->type == APPEND || tmp->type == INPUT)
		&& tmp->next->type == HEREDOC)
		return (msg_error(9));
	if (tmp->type == HEREDOC && tmp->next->type == HEREDOC)
		return (msg_error(8));
	if (tmp->type == APPEND && tmp->next->type == TRUNC)
		return (msg_error(6));
	if (tmp->type == APPEND && tmp->next->type == APPEND)
		return (msg_error(7));
	return (0);
}

char	*check_quote(t_token *tmp, int *i, int *j)
{
	while (tmp->token[*i])
	{
		if (tmp->token[*i] == '\"' || tmp->token[*i] == '\'')
		{
			(*i)++;
			continue ;
		}
		if (tmp->token[*i] != '\"' || tmp->token[*i] != '\'')
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
