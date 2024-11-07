/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:30:24 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/07 15:57:45 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_type(t_token *list)
{
	t_token	*tmp;

	tmp = list;
	if (tmp->type == PIPE && tmp->next->type == PIPE)
		return (msg_error(2));
	return (0);
}

// bool if_open_redirection(char c)
// {
// 	if(c == '>')
// }

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
