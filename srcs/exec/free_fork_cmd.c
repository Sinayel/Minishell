/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fork_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:40:51 by ylouvel           #+#    #+#             */
/*   Updated: 2024/12/15 17:40:59 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_all_fork(t_path *pathlist, t_data *data, t_env *env)
{
	if (data->input)
		free(data->input);
	if (env)
		ft_env_lstclear(&env);
	if (data->cmd)
		free_cmd();
	if (pathlist)
		ft_free_path(pathlist);
	if (data->pipefd[0] >= 0)
		close(data->pipefd[0]);
	if (data->pipefd[1] >= 0)
		close(data->pipefd[1]);
	rl_clear_history();
	if (!access(".tmp.heredoc", F_OK))
		unlink(".tmp.heredoc");
	exit(data->error);
}

void	free_cmd_vars(t_cmd *list)
{
	if (list->infile > 0)
		close(list->infile);
	list->infile = -2;
	if (list->outfile > 0)
		close(list->outfile);
	list->outfile = -2;
	free_tabtab(list->cmd_arg);
	free(list);
	list = NULL;
}
