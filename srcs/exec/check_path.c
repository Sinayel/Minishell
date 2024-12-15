/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:37:48 by ylouvel           #+#    #+#             */
/*   Updated: 2024/12/15 17:38:02 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redir_builtin(t_cmd *cmd, int *pipefd)
{
	close(pipefd[0]);
	if (cmd->outfile < 0 && cmd->next != NULL)
		cmd->outfile = pipefd[1];
	else
		close(pipefd[1]);
}

void	free_export_exec(void)
{
	t_export	*export;

	export = get_export();
	if (export && export->content)
		free_tabtab(export->content);
}

int	built(t_token *list, t_cmd *tcmd, t_env *envlist, t_path *path)
{
	int		save_outfile;
	t_data	*data;

	data = get_data();
	save_outfile = -1;
	if (tcmd->outfile >= 0)
	{
		save_outfile = dup(1);
		dup2(tcmd->outfile, 1);
	}
	if ((ft_strcmp(tcmd->cmd_arg[0], "exit") == 0) && save_outfile >= 0)
		close(save_outfile);
	cmd(tcmd, list, envlist, path);
	if (tcmd && tcmd->outfile >= 0)
	{
		dup2(save_outfile, 1);
		close(save_outfile);
	}
	if (!tcmd->next && data->pid == 4242)
		free_cmd();
	return (0);
}

char	**lst_to_tabtab(t_env *envlist)
{
	char	**tabtab;
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = envlist;
	if (!tmp)
		return (NULL);
	tabtab = (char **)malloc(sizeof(char *) * (cmb_env(tmp) + 1));
	if (!tabtab)
		return (NULL);
	while (tmp)
	{
		tabtab[i] = ft_magouilles(tmp->name, "=", tmp->value);
		tmp = tmp->next;
		i++;
	}
	tabtab[i] = NULL;
	return (tabtab);
}

bool	checkpath(t_path *pathlist, char *cmd, char **path)
{
	int	is_ok;
	int	if_is_ok;

	while (pathlist)
	{
		*path = ft_magouilles(pathlist->name, "/", cmd);
		if_is_ok = access(cmd, X_OK);
		if (if_is_ok == 0)
		{
			*path = ft_strdup(cmd);
			return (true);
		}
		is_ok = access(*path, X_OK);
		if (is_ok == 0)
			return (true);
		pathlist = pathlist->next;
	}
	return (false);
}
