/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:33:31 by ylouvel           #+#    #+#             */
/*   Updated: 2024/12/15 17:42:37 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_process_exit(int pid, int status, t_data *list)
{
	if (pid == list->pid)
	{
		if (WIFEXITED(status))
			list->error = WEXITSTATUS(status);
	}
}

void	close_files(t_cmd *cmd)
{
	if (cmd->infile >= 0)
		close(cmd->infile);
	if (cmd->outfile >= 0)
		close(cmd->outfile);
}

void	wait_and_close(t_cmd *cmd, t_data *list, int len_cmd)
{
	t_cmd	*tmp;
	int		status;
	int		pid;

	tmp = cmd;
	while (len_cmd-- && tmp)
	{
		pid = waitpid(0, &status, 0);
		handle_process_exit(pid, status, list);
		close_files(tmp);
		tmp = tmp->next;
	}
}

void	cleanup_heredoc(void)
{
	if (access(".tmp.heredoc", F_OK) == 0)
		unlink(".tmp.heredoc");
}

void	ft_wait(t_cmd *cmd, t_token *token)
{
	t_data	*list;
	int		len_cmd;

	if (!cmd)
		return ;
	list = get_data();
	len_cmd = len_cmdblocks(token);
	wait_and_close(cmd, list, len_cmd);
	cleanup_heredoc();
}
