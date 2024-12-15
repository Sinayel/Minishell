/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:07:14 by judenis           #+#    #+#             */
/*   Updated: 2024/12/15 16:24:34 by ylouvel          ###   ########.fr       */
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
	t_data	*data;
	t_cmd	**list;
	t_cmd	*tmp;
	t_cmd	*current;
	int		len;

	data = get_data();
	list = &data->cmd;
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
	while (list)
	{
		if (list->type == INPUT || list->type == HEREDOC || list->type == APPEND
			|| list->type == TRUNC)
		{
			if (list->next->type == ARG)
				list = list->next;
			list = list->next;
			continue ;
		}
		if (list->type == PIPE)
			break ;
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
	signal(SIGINT, SIG_DFL);
}

void	ft_embouchure(t_cmd *cmd, t_token *list, t_env *envlist,
		t_path *pathlist, int *pipefd)
{
	int		check;
	t_data	*data;

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
		ft_putstr_fd(" command not found\n", 2);
	}
	free_export_exec();
	ft_token_lstclear(&list);
	free_all_fork(pathlist, pipefd, envlist);
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
		signals2();
		if (cmd->cmd_arg && cmd->cmd_arg[0])
			ft_embouchure(cmd, list, envlist, pathlist, pipefd);
		else
			free_all_fork(pathlist, pipefd, envlist);
	}
	else
		parent_process(pipefd, cmd);
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
		t_token *list, int *pipefd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (initialize_pipe(pipefd))
			return (1);
		exec_cmd(tmp, envlist, pathlist, list, pipefd);
		tmp = tmp->next;
	}
	return (0);
}

void	cleanup_after_execution(t_cmd *cmd, t_token *list)
{
	t_data	*data;

	data = get_data();
	if (cmd) // Vérification ajoutée
		ft_wait(data->cmd, list);
	if (data->cmd || cmd)
		free_cmd();
}

int	ft_exec(t_token *list, t_env *envlist, t_path *pathlist)
{
	t_data	*data;
	int		pipefd[2] = {-1, -1};

	data = get_data();
	data->cmd = token_to_cmd(list);
	if (!data->cmd)
		return (1);
	if (ft_redir(list, data->cmd, envlist) == 1)
		return (1);
	if (handle_single_builtin(data->cmd, list, envlist, pathlist))
		return (0);
	if (execute_commands(data->cmd, envlist, pathlist, list, pipefd))
		return (1);
	cleanup_after_execution(data->cmd, list);
	return (0);
}
