/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:07:14 by judenis           #+#    #+#             */
/*   Updated: 2024/12/15 17:42:28 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_cmd(t_cmd *cmd, t_env *envlist, t_path *pathlist, t_token *list)
{
	t_data	*data;

	data = get_data();
	data->pid = fork();
	if (data->pid < 0)
		return (1);
	else if (!data->pid)
	{
		signals2();
		if (cmd->cmd_arg && cmd->cmd_arg[0])
			ft_embouchure(cmd, list, envlist, pathlist);
		else
			free_all_fork(pathlist, data, envlist);
	}
	else
		parent_process(data->pipefd, cmd);
	return (0);
}

int	handle_single_builtin(t_cmd *tmp, t_token *list, t_env *envlist,
		t_path *pathlist)
{
	if (tmp && tmp->cmd_arg[0] && tmp->next == NULL
		&& is_builtin(tmp->cmd_arg[0]) == true)
		return (built(list, tmp, envlist, pathlist));
	return (0);
}

void	execute_child_process(t_exec_context *ctx, t_data *data, int *pipefd)
{
	char	*path;
	char	**env_tab;

	path = NULL;
	env_tab = NULL;
	handle_redirection(ctx->cmd, pipefd);
	if (checkpath(ctx->pathlist, ctx->cmd->cmd_arg[0], &path))
	{
		env_tab = lst_to_tabtab(ctx->envlist);
		signals2();
		execve(path, ctx->cmd->cmd_arg, env_tab);
	}
	if (path)
		free(path);
	if (env_tab)
		free_tabtab(env_tab);
	signal(SIGINT, SIG_DFL);
	free_all_fork(ctx->pathlist, data, ctx->envlist);
}

int	execute_command(t_exec_context *ctx, int *pipefd)
{
	t_data	*data;

	data = get_data();
	data->pid = fork();
	if (data->pid < 0)
		return (1);
	else if (data->pid == 0)
		execute_child_process(ctx, data, pipefd);
	else
		handle_parent_process(pipefd, ctx->cmd);
	return (0);
}

int	ft_exec(t_token *list, t_env *envlist, t_path *pathlist)
{
	t_data	*data;

	data = get_data();
	data->pipefd[0] = -1;
	data->pipefd[1] = -1;
	data->cmd = token_to_cmd(list);
	if (!data->cmd)
		return (1);
	if (ft_redir(list, data->cmd, envlist) == 1)
		return (1);
	if (handle_single_builtin(data->cmd, list, envlist, pathlist))
		return (0);
	if (execute_commands(data->cmd, envlist, pathlist, list))
		return (1);
	cleanup_after_execution(data->cmd, list);
	return (0);
}
