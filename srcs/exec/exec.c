/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:07:14 by judenis           #+#    #+#             */
/*   Updated: 2024/12/14 17:08:40 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_all_fork(t_path *pathlist, int *pipefd, t_env *env)
{
	t_data	*list;

	list = get_data();
	if (list->input)
		free(list->input);
	if (env)
		ft_env_lstclear(&env);
	if (list->cmd)
		free_cmd();
	if (pathlist)
		ft_free_path(pathlist);
	if (pipefd[0] >= 0)
		close(pipefd[0]);
	if (pipefd[1] >= 0)
		close(pipefd[1]);
	rl_clear_history();
	if (!access(".tmp.heredoc", F_OK))
		unlink(".tmp.heredoc");
	exit(list->error);
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

void	free_cmd(void)
{
    t_data *data;
    data = get_data();
    t_cmd **list = &data->cmd;
	t_cmd	*tmp;
	t_cmd	*current;
	int		len;

	if (list == NULL || *list == NULL)
		return ;
	len = len_cmd(*list) - 1;
	current = *list;
	while (current && len--)
	{
		tmp = current;
		current = current->next;
		free_cmd_vars(tmp);
	}
	free_cmd_vars(current);
	*list = NULL;
}

int	len_cmd(t_cmd *list)
{
	int		len;
	t_cmd	*tmp;

	len = 0;
	if (!list)
		return (0);
	tmp = list;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

int	len_cmdblocks(t_token *list)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = list;
	while (tmp)
	{
		if (tmp->type == CMD)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int	len_in_block(t_token *list)
{
	int	len;

	len = 0;
	while (list && (list->type == CMD || list->type == ARG))
	{
		len++;
		list = list->next;
	}
	return (len);
}

bool	is_builtin(char *str)
{
	if (ft_strcmp(str, "cd") == 0 || ft_strcmp(str, "pwd") == 0
		|| ft_strcmp(str, "unset") == 0 || ft_strcmp(str, "env") == 0
		|| ft_strcmp(str, "echo") == 0 || ft_strcmp(str, "exit") == 0
		|| ft_strcmp(str, "export") == 0)
		return (true);
	return (false);
}

void	print_cmd(t_cmd *list)
{
	t_cmd	*tmp;
	int		i;
	int		len;

	tmp = list;
	len = 0;
	i = 0;
	while (tmp)
	{
		i = 0;
		while (tmp->cmd_arg[i])
		{
			printf("noeud n.%d = [%s] ->\n", len, tmp->cmd_arg[i]);
			i++;
		}
		len++;
		tmp = tmp->next;
	}
	printf("-> NULL\n");
}

void	redir_builtin(t_cmd *cmd, int *pipefd)
{
	close(pipefd[0]);
	if (cmd->outfile < 0)
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
	char	*cmd_buff;
	t_data	*data;

	data = get_data();
	cmd_buff = ft_strdup(tcmd->cmd_arg[0]);
	save_outfile = -1;
    if (tcmd->outfile >= 0)
	{
		save_outfile = dup(1);
		dup2(tcmd->outfile, 1);
	}
	if ((ft_strcmp(cmd_buff, "exit") == 0) && save_outfile >= 0)
		close(save_outfile);
	cmd(&cmd_buff, list, envlist, path);
	if (tcmd && tcmd->outfile >= 0)
	{
		dup2(save_outfile, 1);
		close(save_outfile);
	}
	if (!tcmd->next && data->pid == 4242)
		free_cmd();
	if (cmd_buff != NULL)
		free(cmd_buff);
	return (0);
}

t_cmd	*token_to_cmd(t_token *list)
{
	t_token	*tmp;
	t_cmd	*cmd_head;
	t_cmd	*cmd_tail;
	t_cmd	*new_cmd;
	int		i;

	tmp = list;
	cmd_head = NULL;
	cmd_tail = NULL;
	while (tmp)
	{
		if (tmp->type == CMD)
		{
			new_cmd = malloc(sizeof(t_cmd));
			if (!new_cmd)
			{
				if(cmd_head)
					free_cmd();
				return (NULL);
			}
			new_cmd->next = NULL;
			new_cmd->cmd_arg = malloc(sizeof(char *) * (len_in_block(tmp) + 1));
			if (!new_cmd->cmd_arg)
			{
				if(cmd_head)
					free_cmd();
				free(new_cmd);
				return (NULL);
			}
			i = 0;
			while (tmp && (tmp->type == CMD || tmp->type == ARG))
			{
				new_cmd->cmd_arg[i] = ft_strdup(tmp->token);
				if (!new_cmd->cmd_arg[i])
				{
					while (i > 0)
						free(new_cmd->cmd_arg[--i]);
					free(new_cmd->cmd_arg);
					free(new_cmd);
					if(cmd_head)
						free_cmd();
					return (NULL);
				}
				tmp = tmp->next;
				i++;
			}
			new_cmd->cmd_arg[i] = NULL;
			new_cmd->infile = -2;
			new_cmd->outfile = -2;
			if (!cmd_head)
				cmd_head = new_cmd;
			else
				cmd_tail->next = new_cmd;
			cmd_tail = new_cmd;
		}
		else
			tmp = tmp->next;
		if (cmd_head)
		    free_cmd();
	}
	return (cmd_head);
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
		int *pipefd)
{
	char	*path;
	char	**tabtab;

	tabtab = NULL;
	path = NULL;
	redir_in_out(list, pipefd);
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
	// signal(SIGINT, SIG_DFL);
}

void	ft_embouchure(t_cmd *cmd, t_token *list, t_env *envlist,
		t_path *pathlist, int *pipefd)
{
	int	check;
	t_data *data;

	data = get_data();
	check = double_check(pathlist, cmd->cmd_arg[0]);
	if (is_builtin(cmd->cmd_arg[0]) == true)
	{
		redir_builtin(cmd, pipefd);
		built(list, cmd, envlist, pathlist);
	}
	else if (is_builtin(cmd->cmd_arg[0]) == false && check == 0)
		not_builtin_child(cmd, envlist, pathlist, pipefd);
	else if (check == 1 && is_builtin(cmd->cmd_arg[0]) == false)
	{
		data->error = 127;
		ft_putstr_fd(" Command not found\n", 2);
	}
	free_export_exec();
	ft_token_lstclear(&list);
	free_all_fork(pathlist, pipefd, envlist);
}

int	heredoc_handler(char *str, t_env *envlist, int fd)
{
	char	*line;

	while (1)
	{
		line = readline(">");
		if (!line)
		{
			write(2,
				"bash :warning: here-document delimited by end-of-file (wanted `",
				64);
			write(2, str, ft_strlen(str));
			write(2, "`)\n", 3);
			close(fd);
			return (0);
		}
		if (ft_strcmp(line, str) == 0)
			break ;
		if (ft_strcmp(line, "") != 0)
		{
			if (line)
			{
				line = proccess_dollar_value(line, envlist);
				if (line)
					write(fd, line, ft_strlen(line));
			}
		}
		write(fd, "\n", 1);
		if (line)
			free(line);
	}
	if (line)
		free(line);
	close(fd);
	return (0);
}

int	here_doc(t_env *envlist, char *str)
{
	int	fd;

	fd = open(".tmp.heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	if (heredoc_handler(str, envlist, fd))
	{
		printf("here_doc = %d\n", fd);
		unlink(".tmp.heredoc");
		return (-1);
	}
	fd = open(".tmp.heredoc", O_RDONLY);
	if (fd > 0)
		unlink(".tmp.heredoc");
	return (fd);
}

int	ft_redir(t_token *list, t_cmd *cmd, t_env *envlist)
{
	t_token	*tmp;
	t_cmd	*cmdt;

	cmdt = cmd;
	tmp = list;
	while (tmp) //! faudrait ptet parcourir t_cmd plutot que t_token
	{
		if (tmp->type == INPUT)
		{
			if (cmdt->infile >= 0)
				close(cmdt->infile);
			cmdt->infile = open(tmp->next->token, O_RDONLY);
		}
		if (tmp->type == HEREDOC)
		{
			if (cmdt->infile >= 0)
				close(cmdt->infile);
			cmdt->infile = here_doc(envlist, tmp->next->token);
		}
		while (cmdt->next != NULL)
			cmdt = cmdt->next;
		if (tmp->type == TRUNC)
		{
			if (cmdt->outfile >= 0)
				close(cmdt->outfile);
			cmdt->outfile = open(tmp->next->token, O_CREAT | O_RDWR | O_TRUNC,
					0644);
		}
		if (tmp->type == APPEND)
		{
			if (cmdt->outfile >= 0)
				close(cmdt->outfile);
			cmdt->outfile = open(tmp->next->token, O_CREAT | O_RDWR | O_APPEND,
					0644);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	ft_wait(t_cmd *cmd, t_token *token)
{
	int		status;
	int		len_cmd;
	t_data	*list;
	t_cmd	*tmp;
	int		pid;

	list = get_data();
	len_cmd = len_cmdblocks(token);
	tmp = cmd;
	while (len_cmd--)
	{
		pid = waitpid(0, &status, 0);
		if (pid == list->pid)
		{
			if (WIFEXITED(status))
				list->error = WEXITSTATUS(status);
		}
		if (tmp->infile >= 0)
			close(tmp->infile);
		if (tmp->outfile >= 0)
			close(tmp->outfile);
		tmp = tmp->next;
	}
	if (access(".tmp.heredoc", F_OK) == 0)
		unlink(".tmp.heredoc");
}

int	exec_cmd(t_cmd *cmd, t_env *envlist, t_path *pathlist, t_token *list,
		int *pipefd)
{
	t_data	*data;

	data = get_data();
	data->pid = fork();
	if (data->pid < 0)
		return (1);
	else if (!data->pid)
	{
		if (cmd->cmd_arg && cmd->cmd_arg[0])
			ft_embouchure(cmd, list, envlist, pathlist, pipefd);
		else
			free_all_fork(pathlist, pipefd, envlist);
	}
	else
		parent_process(pipefd, cmd);
	return (0);
}

int	ft_exec(t_token *list, t_env *envlist, t_path *pathlist)
{
	t_cmd	*tmp;
	int		pipefd[2];
	t_data	*data;

	data = get_data();
	pipefd[0] = -1;
	pipefd[1] = -1;
	data->cmd = token_to_cmd(list);
	tmp = data->cmd;
	if (!tmp)
		return (1);
	ft_redir(list, tmp, envlist);
	if (data->cmd && data->cmd->cmd_arg[0] && data->cmd->next == NULL
		&& is_builtin(tmp->cmd_arg[0]) == true)
		return (built(list, tmp, envlist, pathlist));
	if (pipe(pipefd) == -1)
	{
		free_cmd();
		return (1);
	}
	exec_cmd(tmp, envlist, pathlist, list, pipefd);
	tmp = tmp->next;
	while (tmp)
	{
		if (pipe(pipefd) == -1)
		{
			free_cmd();
			return (1);
		}
		exec_cmd(tmp, envlist, pathlist, list, pipefd);
		tmp = tmp->next;
	}
	ft_wait(data->cmd, list);
	if (data->cmd || tmp)
		free_cmd();
	// if (pipefd[0] >= 0)
	// 	close(pipefd[0]);
	// if (pipefd[1] >= 0)
	// 	close(pipefd[1]);
	return (0);
}
