/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:14:05 by ylouvel           #+#    #+#             */
/*   Updated: 2024/12/04 18:13:37 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cmd(char *str, t_token *list, t_env *env, t_data *data)
{
	if (ft_strcmp(str, "cd") == 0)
		return (ft_arg_cd(env, list, data));
	if (ft_strcmp(str, "pwd") == 0)
		return (ft_pwd(NULL));
	if (ft_strcmp(str, "unset") == 0)
		return (ft_arg_unset(env, list));
	if (ft_strcmp(str, "env") == 0)
		return (print_env(env));
	if (ft_strcmp(str, "echo") == 0)
		return (echo(list));
	if (ft_strcmp(str, "exit") == 0)
		return (0);
	if (ft_strcmp(str, "export") == 0)
		return (ft_arg_export(env, list));
	if (ft_strcmp(str, "") == 0)
		return (1);
	return (1);
}

int	parsing_exec(t_token *list, t_env *env, t_data *data)
{
	if (check_pipe(list) != 0)
	{
		data->error = 2;
		ft_putstr_fd("error pipe\n", 2);
		return (1);
	}
	if (check_redirection(list) != 0)
	{
		data->error = 2;
		ft_putstr_fd("error redirection\n", 2);
		return (1);
	}
	if (check_cmd(list, env, data) == 1)
	{
		ft_putstr_fd("command not found\n", 2);
		return (1);
	}
	else if (!check_if_exit(list, env))
		return (1);
	return (0);
}
