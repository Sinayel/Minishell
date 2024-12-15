/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:30:56 by ylouvel           #+#    #+#             */
/*   Updated: 2024/12/15 17:31:12 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	initialize_pipe(int *pipefd)
{
	if (pipe(pipefd) == -1)
	{
		free_cmd();
		return (1);
	}
	return (0);
}

int	execute_commands(t_cmd *cmd, t_env *envlist, t_path *pathlist,
		t_token *list)
{
	t_data	*data;
	t_cmd	*tmp;

	data = get_data();
	tmp = cmd;
	while (tmp)
	{
		if (pipe(data->pipefd) == -1)
			return (1);
		if (exec_cmd(tmp, envlist, pathlist, list))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	cleanup_after_execution(t_cmd *cmd, t_token *list)
{
	t_data	*data;

	data = get_data();
	if (cmd)
		ft_wait(data->cmd, list);
	if (data->cmd || cmd)
		free_cmd();
}

void	handle_redirection(t_cmd *cmd, int *pipefd)
{
	close(pipefd[0]);
	if (cmd->infile >= 0)
	{
		dup2(cmd->infile, 0);
		close(cmd->infile);
	}
	if (cmd->outfile >= 0)
	{
		dup2(cmd->outfile, 1);
		close(cmd->outfile);
	}
	else if (cmd->next)
		dup2(pipefd[1], 1);
	close(pipefd[1]);
}

int	handle_parent_process(int *pipefd, t_cmd *cmd)
{
	close(pipefd[1]);
	if (cmd->infile >= 0)
		close(cmd->infile);
	if (cmd->infile == -2)
		cmd->infile = pipefd[0];
	if (cmd->next != NULL && cmd->next->infile == -2)
		cmd->next->infile = pipefd[0];
	else
		close(pipefd[0]);
	return (0);
}
