/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:21:59 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/12 18:55:45 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// 5 Fonction pour verifier si c'est une cmd ou un argument
t_token	*cmd_token(t_token *list)
{
	t_token	*tmp;
	t_token	*last;

	tmp = list;
	tmp->first = 1;
	tmp->type = CMD;
	last = tmp;
	tmp = tmp->next;
	while (tmp != NULL)
	{
		if (last->type == PIPE && tmp->type == ARG)
			tmp->type = CMD;
		else if (tmp->type != PIPE && tmp->type >= PIPE)
			tmp->type = ARG;
		last = tmp;
		tmp = tmp->next;
	}
	return (list);
}

t_token	*id_token(t_token *list)
{
	t_token	*tmp;
	t_token	*tmp2;

	tmp = list;
	tmp2 = list;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->token, "|") == 0)
			tmp->type = PIPE;
		else if (ft_strcmp(tmp->token, ">>") == 0)
			tmp->type = APPEND;
		else if (ft_strcmp(tmp->token, "<<") == 0)
			tmp->type = HEREDOC;
		else if (ft_strcmp(tmp->token, ">") == 0)
			tmp->type = TRUNC;
		else if (ft_strcmp(tmp->token, "<") == 0)
			tmp->type = INPUT;
		else
			tmp->type = ARG;
		tmp = tmp->next;
	}
	tmp2 = cmd_token(tmp2);
	return (list);
}
