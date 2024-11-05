/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:14:05 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/05 21:24:14 by ylouvel          ###   ########.fr       */
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
		if ((tmp->next == NULL && tmp->type == PIPE) || (tmp->type == PIPE
				&& (tmp->next->type == TRUNC || tmp->next->type == APPEND
					|| tmp->next->type == INPUT)))
		{
			ft_putstr_fd("minishell: syntax error unexpected token `|'\n", 2);
			return (1);
		}
		if (tmp->next != NULL)
		{
			if ((tmp->type == PIPE && tmp->next->type == PIPE)
				|| (tmp->first == 1 && strcmp(tmp->token, "|") == 0))
			{
				ft_putstr_fd("minishell: syntax error unexpected token `|'\n",
					2);
				return (1);
			}
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

//? Pour enlever les doubles quotes des noeud de la liste chainee
t_token	*remove_quote(t_token *list)
{
	t_token	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = list;
	while (tmp)
	{
		if (tmp->type == CMD || tmp->type == ARG)
		{
			tmp->token = check_quote(tmp, &i, &j);
			i = 0;
			j = 0;
		}
		tmp = tmp->next;
	}
	return (list);
}

int	parsing(t_token *list)
{
	if (check_pipe(list) == 1)
		return (1);
	if (check_redirection(list) == 1)
		return (1);
	// 1 -------------------  Check if there is a good word  -------------------
	return (0);
}
