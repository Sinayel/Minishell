/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:14:05 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/25 19:38:26 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cmd(char *str, t_token *list, t_env *env, t_data *data, t_path *path)
{
	if (ft_strcmp(str, "cd") == 0)
		return (ft_arg_cd(env, list));
	if (ft_strcmp(str, "pwd") == 0)
		return (ft_pwd(NULL));
	if (ft_strcmp(str, "unset") == 0)
		return (1);
	if (ft_strcmp(str, "env") == 0)
		return (print_env(env));
	if (ft_strcmp(str, "echo") == 0)
		return (echo(list));
	if (ft_strcmp(str, "exit") == 0)
		return (ft_exit(list, data, env, path));
	if (ft_strcmp(str, "export") == 0)
		return (ft_arg_export(env, list));			// Pas encore bon pour les ajouts de plusieur var dans l'env
	return 1;
}

//! A MODIFIER APRES PIPEX SI BESOIN !!!
// 6 Check si la premiere redirection n'est suivit de rien, et check les cas suivants
int	check_redirection(t_token *list)
{
	t_token	*tmp;

	tmp = list;
	if (tmp && is_redirection(tmp->token) && tmp->next == NULL)
		return (msg_error(2));
	while (tmp)
	{
		if (tmp->type == TRUNC || tmp->type == APPEND || tmp->type == INPUT
			|| tmp->type == HEREDOC)
		{
			if (tmp->next == NULL || tmp->next->type == PIPE)
				return (msg_error(1));
			if ((tmp->next->type == TRUNC || tmp->next->type == APPEND
					|| tmp->next->type == INPUT || tmp->next->type == HEREDOC)
				&& tmp->next == NULL)
				return (msg_error(1));
		}
		tmp = tmp->next;
	}
	return (0);
}

// 6 Check si les commandes sont dans le path ou si elles ont deja etaient creer
int	check_cmd(t_token *list, t_env *env, t_data *data)
{
	t_token	*tmp;
	t_path	*path;

	path = return_path(env);
	tmp = list;
	while (tmp)
	{
		if (tmp->type == CMD && cmd(tmp->token, tmp, env, data, path) == 1)	// Si la commande n'est aps trv dans les commandes creer alors on check dans les paths
		{
			if (double_check(path, tmp) == 1)	// Si les commandes ne sont tjr pas trv alors on free le path
			{
				if (path)
					ft_free_path(path);
				return (1);
			}
			printf("Ok\n");
		}
		tmp = tmp->next;
	}
	if (path)
		ft_free_path(path);
	return (0);
}

// 6 Check le premier '|' puis regarde les erreurs pour les suivants
int	check_pipe(t_token *list)
{
	t_token	*tmp;

	tmp = list;
	if (tmp && ft_strcmp(tmp->token, "|") == 0)
		return (msg_error(2));
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			if (tmp->next == NULL)
				return (msg_error(2));
			if (tmp->next->type == PIPE)
				return (msg_error(2));
		}
		if (tmp->next != NULL && check_type(tmp) != 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	parsing(t_token *list, t_env *env, t_data *data)
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
	if (check_cmd(list, env, data) != 0)
	{
		data->error = 127;
		ft_putstr_fd("command not found\n", 2);
		return (1);
	}
	// data->error = 0;
	return (0);
}
