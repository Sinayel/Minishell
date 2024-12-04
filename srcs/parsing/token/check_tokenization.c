/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokenization.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:23:26 by ylouvel           #+#    #+#             */
/*   Updated: 2024/12/04 19:05:53 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// 6 Check si les commandes sont dans le path ou si elles ont deja etaient creer
int	check_cmd(t_token *list, t_env *env, t_data	*data)
{
	t_token	*tmp;
	t_path	*path;

	path = return_path(env);
	tmp = list;
	while (tmp)
	{
		if ((tmp->type == CMD && cmd(tmp->token, tmp, env, data) == 1
				&& env->next))
		{
			if (double_check(path, tmp, tmp->token) == 1)
			{
				if (path)
					ft_free_path(path);
				data->error = 127;
				return (1);
			}
			printf("Ok (exec cmd)\n");
		}
		tmp = tmp->next;
	}
	if (env->next)
		ft_free_path(path);
	return (0);
}

//! A MODIFIER APRES PIPEX SI BESOIN !!!
int	check_redirection(t_token *list)
{
	t_token	*tmp;

	tmp = list;
	if (tmp && is_redirection(tmp->token) && tmp->next == NULL)
		return (msg_error(1));
	while (tmp)
	{
		if (tmp->type < CMD)
		{
			if (tmp->next && tmp->next->next)
				if (return_next_next(tmp) == 1)
					return (1);
			if (for_trunc_and_heredoc(tmp) == 1)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	check_pipe(t_token *list)
{
	t_token	*tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->type == PIPE && tmp->first == 1 && !tmp->next)
			return (msg_error(2));
		if (tmp->prev)
			if ((tmp->prev->type == INPUT || tmp->prev->type == TRUNC)
				&& tmp->type == PIPE)
				return (msg_error(1));
		if (tmp->type == PIPE)
		{
			if (!tmp->next)
				return (msg_error(2));
			if (tmp->next->type == PIPE)
				return (msg_error(5));
			if (!tmp->prev)
				return (msg_error(2));
		}
		tmp = tmp->next;
	}
	return (0);
}
