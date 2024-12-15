/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   embouchure.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:35:47 by ylouvel           #+#    #+#             */
/*   Updated: 2024/12/15 17:36:06 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parent_process(int *fd, t_cmd *cmd)
{
	t_data	*data;

	data = get_data();
	close(fd[1]);
	if (cmd->infile >= 0)
		close(cmd->infile);
	if (cmd->infile == -2)
		cmd->infile = fd[0];
	if (cmd->next != NULL && cmd->next->infile == -2)
		cmd->next->infile = fd[0];
	else
		close(fd[0]);
	return (data->error);
}

void	redir_in_out(t_cmd *list, int *fd)
{
	close(fd[0]);
	if (list->infile >= 0)
	{
		dup2(list->infile, 0);
		close(list->infile);
	}
	if (list->outfile >= 0)
	{
		dup2(list->outfile, 1);
		close(list->outfile);
	}
	else if (list->next)
		dup2(fd[1], 1);
	close(fd[1]);
}

void	not_builtin_child(t_cmd *list, t_env *envlist, t_path *pathlist,
		t_data *data)
{
	char	*path;
	char	**tabtab;

	tabtab = NULL;
	path = NULL;
	redir_in_out(list, data->pipefd);
	if (checkpath(pathlist, list->cmd_arg[0], &path))
	{
		tabtab = lst_to_tabtab(envlist);
		signals2();
		execve(path, list->cmd_arg, tabtab);
	}
	if (path)
		free(path);
	if (tabtab)
		free_tabtab(tabtab);
	signal(SIGINT, SIG_DFL);
}

void	ft_embouchure(t_cmd *cmd, t_token *list, t_env *envlist,
		t_path *pathlist)
{
	int		check;
	t_data	*data;

	data = get_data();
	check = double_check(pathlist, cmd->cmd_arg[0]);
	if (is_builtin(cmd->cmd_arg[0]) == true)
	{
		redir_builtin(cmd, data->pipefd);
		built(list, cmd, envlist, pathlist);
	}
	else if (is_builtin(cmd->cmd_arg[0]) == false && check == 0)
		not_builtin_child(cmd, envlist, pathlist, data);
	else if (check == 1 && is_builtin(cmd->cmd_arg[0]) == false)
	{
		data->error = 127;
		ft_putstr_fd(" command not found\n", 2);
	}
	free_export_exec();
	ft_token_lstclear(&list);
	free_all_fork(pathlist, data, envlist);
}

int	check_access_redir(char *str)
{
	t_data	*data;

	data = get_data();
	if (access(str, W_OK | R_OK) == -1)
	{
		if (errno == ENOENT)
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			data->error = 1;
			return (1);
		}
		if (errno == EACCES)
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": Permission denied\n", 2);
			data->error = 1;
			return (1);
		}
	}
	return (0);
}
