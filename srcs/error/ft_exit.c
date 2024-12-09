/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:12:34 by ylouvel           #+#    #+#             */
/*   Updated: 2024/12/02 12:31:27 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	for_check_exit(char *str, t_token *list, t_env *env, t_path *path)
{
	if (ft_strcmp(str, "exit") == 0)
		return (ft_exit(list, env, path));
	return (0);
}

int	check_if_exit(t_token *list, t_env *env)
{
	t_token	*tmp;
	t_path	*path;

	if (env->next)
		path = return_path(env);
	tmp = list;
	while (tmp)
	{
		if (tmp->type == CMD && for_check_exit(tmp->token, tmp, env, path) == 2
			&& env->next)
		{
			if (path)
				ft_free_path(path);
			return (1);
		}
		tmp = tmp->next;
	}
	if (env->next)
		ft_free_path(path);
	return (0);
}
