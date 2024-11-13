/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:30:24 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/13 15:09:30 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	check_unclosed_pipe(t_token *token_list)
{
	t_token	*current;

	current = token_list;
	while (current)
	{
		if (current->type == PIPE && current->next == NULL)
		{
			printf("Error: Unclosed pipe\n");
			return (true);
		}
		current = current->next;
	}
	return (false);
}

int	check_type(t_token *list)
{
	t_token	*tmp;

	tmp = list;
	if (tmp->type == PIPE && tmp->next->type == PIPE)
		return (msg_error(2));
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
