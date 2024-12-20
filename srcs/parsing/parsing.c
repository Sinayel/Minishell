/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:14:05 by ylouvel           #+#    #+#             */
/*   Updated: 2024/12/15 14:23:01 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cmd(t_cmd *cmd, t_token *list, t_env *env, t_path *path)
{
	if (ft_strcmp(cmd->cmd_arg[0], "cd") == 0)
		return (ft_arg_cd(env, list));
	else if (ft_strcmp(cmd->cmd_arg[0], "pwd") == 0)
		return (ft_pwd(NULL));
	else if (ft_strcmp(cmd->cmd_arg[0], "unset") == 0)
		return (ft_arg_unset(env, list));
	else if (ft_strcmp(cmd->cmd_arg[0], "env") == 0)
		return (print_env(env));
	else if (ft_strcmp(cmd->cmd_arg[0], "echo") == 0)
		return (echo(cmd));
	else if (ft_strcmp(cmd->cmd_arg[0], "exit") == 0)
		return (feat_arg_exit(list, env, path));
	else if (ft_strcmp(cmd->cmd_arg[0], "export") == 0)
		return (ft_arg_export(env, list));
	return (1);
}

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

int	check_cmd(t_token *list, t_env *env)
{
	t_token	*tmp;
	t_path	*path;

	path = return_path(env);
	tmp = list;
	ft_exec(tmp, env, path);
	if (path)
		ft_free_path(path);
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
	return (check_cmd(list, env) == 1);
}
