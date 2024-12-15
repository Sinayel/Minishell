/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 15:46:59 by ylouvel           #+#    #+#             */
/*   Updated: 2024/12/15 15:47:26 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_input_redirection(t_token *tmp, t_cmd *cmdt, int *err)
{
	char	*tmp_path;

	tmp_path = tmp->next->token;
	if (cmdt->infile >= 0)
		close(cmdt->infile);
	cmdt->infile = open(tmp->next->token, O_RDONLY);
	*err = check_access_redir(tmp_path);
	return (*err);
}

int	handle_heredoc_redirection(t_token *tmp, t_cmd *cmdt, t_env *envlist)
{
	char	*tmp_path;

	tmp_path = tmp->next->token;
	if (cmdt->infile >= 0)
		close(cmdt->infile);
	cmdt->infile = here_doc(envlist, tmp->next->token);
	return (0);
}

int	handle_trunc_redirection(t_token *tmp, t_cmd *cmdt, int *err)
{
	char	*tmp_path;

	tmp_path = tmp->next->token;
	if (cmdt->outfile >= 0)
		close(cmdt->outfile);
	cmdt->outfile = open(tmp->next->token, O_CREAT | O_RDWR | O_TRUNC, 0644);
	*err = check_access_redir(tmp_path);
	return (*err);
}

int	handle_append_redirection(t_token *tmp, t_cmd *cmdt, int *err)
{
	char	*tmp_path;

	tmp_path = tmp->next->token;
	if (cmdt->outfile >= 0)
		close(cmdt->outfile);
	cmdt->outfile = open(tmp->next->token, O_CREAT | O_RDWR | O_APPEND, 0644);
	*err = check_access_redir(tmp_path);
	return (*err);
}

int	ft_redir(t_token *list, t_cmd *cmd, t_env *envlist)
{
	t_token	*tmp;
	t_cmd	*cmdt;
	int		err;

	cmdt = cmd;
	tmp = list;
	err = 0;
	while (tmp && cmdt)
	{
		if (tmp->type == PIPE)
			cmdt = cmdt->next;
		else if (tmp->type == INPUT)
			err = handle_input_redirection(tmp, cmdt, &err);
		else if (tmp->type == HEREDOC)
			handle_heredoc_redirection(tmp, cmdt, envlist);
		else if (tmp->type == TRUNC)
			err = handle_trunc_redirection(tmp, cmdt, &err);
		else if (tmp->type == APPEND)
			err = handle_append_redirection(tmp, cmdt, &err);
		if (err == 1)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
