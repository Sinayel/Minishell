/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:14:05 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/06 19:39:50 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cmd(char *str, t_token *list, t_env *env)
{
	(void)list;
	(void)env;
	if (ft_strcmp(str, "cd") == 0)
		return (1);
	if (ft_strcmp(str, "pwd") == 0)
		return (1);
	if (ft_strcmp(str, "unset") == 0)
		return (1);
	if (ft_strcmp(str, "env") == 0)
		return (1);
	if (ft_strcmp(str, "echo") == 0)
		return (1);
	if (ft_strcmp(str, "exit") == 0)
		return (1);
	if (ft_strcmp(str, "export") == 0)
		return (1);
	return (0);
}

int	check_cmd(t_token *list, t_env *env)
{
	t_token	*tmp;
	t_path	*path;

	path = return_path(env);
	tmp = list;
	while (tmp)
	{
		if (tmp->type == CMD && cmd(tmp->token, list, env) == 0)
		{
			if (double_check(path, tmp) == 1)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	parsing(t_token *list, t_env *env)
{
	if (check_pipe(list) == 1)
		return (1);
	if (check_redirection(list) == 1)
		return (1);
	if (check_cmd(list, env) == 1)
	{
		printf("Pas bon...\n");
		return (1);
	}
	return (0);
}
