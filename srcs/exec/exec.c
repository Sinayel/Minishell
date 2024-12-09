/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:07:14 by judenis           #+#    #+#             */
/*   Updated: 2024/12/10 21:35:52 by judenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    free_all_fork(t_cmd *cmdlist, t_path *pathlist, int *pipefd, t_env *env)
{
    t_data *list;

    (void)cmdlist;
    list = get_data();
    // if (datalist->input)
    //     free(datalist->input);
    // if (list)
    //     ft_token_lstclear(&list);
    if (list->input)
        free(list->input);
    if (env)
        ft_env_lstclear(&env);
    if (cmdlist)
        free_cmd(&cmdlist);
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

void free_cmd_vars(t_cmd *list)
{
    if (list->infile > 0)
        close(list->infile);
    list->infile = -2;
    if (list->outfile > 0)
        close(list->outfile);
    list->outfile = -2;
    free_tabtab(list->cmd_arg);
}

void free_cmd(t_cmd **list)
{
    t_cmd *tmp;
    t_cmd *current;
    int len;

    if (list == NULL || *list == NULL)
        return;
    len  = len_cmd(*list) - 1;
    current = *list;
    while (current && len--)
    {
        tmp = current;
        current = current->next;
        free_cmd_vars(tmp);
        free(tmp);
    }
    free_cmd_vars(current);
    free(current);
    *list = NULL;
}

// void free_cmd(t_cmd **list)
// {
//     t_cmd *tmp;
//     t_cmd *next;

//     if (list == NULL || *list == NULL)
//         return;
//     tmp = *list;
//     while (tmp)
//     {
//         next = tmp->next;
//         // Libération des arguments de la commande
//         if (tmp->infile >= 0)
//             close(tmp->infile);
//         if (tmp->outfile >= 0)
//             close(tmp->outfile);
//         if (tmp->cmd_arg)
//         {
//             free_tabtab(tmp->cmd_arg);
//             tmp->cmd_arg = NULL;
//         }
//         // Libération du nœud de commande
//         free(tmp);
//         tmp = next;
//     }
//     if (access(".tmp.heredoc", F_OK) == 0)
//         unlink(".tmp.heredoc");
//     // Mettre le pointeur original à NULL
//     *list = NULL;
// }

int len_cmd(t_cmd *list)
{
    int len;
    t_cmd *tmp;

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

int len_cmdblocks(t_token *list)
{
    t_token *tmp;
    int i;

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

int len_in_block(t_token *list)
{
    int len;

    len = 0;
    while (list && (list->type == CMD || list->type == ARG))
    {
        len++;
        list = list->next;
    }
    return (len);
}

bool is_builtin(char *str)
{
    if (ft_strcmp(str, "cd") == 0|| ft_strcmp(str, "pwd") == 0 || ft_strcmp(str, "unset") == 0 || ft_strcmp(str, "env") == 0 || ft_strcmp(str, "echo") == 0 || ft_strcmp(str, "exit") == 0 || ft_strcmp(str, "export") == 0)
		return true;
    return false;
}

void print_cmd(t_cmd *list)
{
    t_cmd *tmp;

    tmp = list;
    int i;
    int len = 0;
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

int launch_builtin(t_token *list, t_env *envlist, t_path *path)
{
    t_token *tmp;
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! PROBLEEEEEEEEEEEEEEEEMMMMMMMMEEEEEEEEE   !!!!
    tmp = list;

    while (tmp)
    {
        if (tmp->type == CMD)
            cmd(tmp->token, tmp, envlist, path);
        tmp = tmp->next;
    }
    return (0); 
}

static void redir_builtin(t_cmd *cmdlist, int *pipefd)
{
    close(pipefd[0]);
    if (cmdlist->outfile < 0 && cmdlist)
        cmdlist->outfile = pipefd[1];
    else
        close(pipefd[1]);
}

void free_export_exec(void)
{
    t_export *export;

    export = get_export();
    if (export && export->content)
        free_tabtab(export->content);
}

static int built(t_token *list, t_cmd *cmdlist, t_env *envlist, t_path *pathlist)
{
    int save_outfile;
    char *cmd_buff;

    cmd_buff = ft_strdup(cmdlist->cmd_arg[0]);
    save_outfile = -1;
    if (cmdlist->outfile >= 0)
    {
        save_outfile = dup(1);
        dup2(cmdlist->outfile, 1);
    }
    if (ft_strcmp(cmd_buff, "exit") == 0)
        free_cmd(&cmdlist);
    cmd(cmd_buff, list, envlist, pathlist);
    if (cmdlist && cmdlist->outfile >= 0)
    {
        dup2(save_outfile, 1);
        close(save_outfile);
    }
    free(cmd_buff);
    return (0);
}

t_cmd *token_to_cmd(t_token *list)
{
    t_token *tmp = list;
    t_cmd *cmd_head = NULL;
    t_cmd *cmd_tail = NULL;
    t_cmd *new_cmd;
    int i;

    while (tmp)
    {
        if (tmp->type == CMD)
        {
            new_cmd = malloc(sizeof(t_cmd));
            if (!new_cmd)
                return (NULL);
            new_cmd->next = NULL;
            new_cmd->cmd_arg = malloc(sizeof(char *) * (len_in_block(tmp) + 1));
            if (!new_cmd->cmd_arg)
            {
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
    }
    return (cmd_head);
}

char **lst_to_tabtab(t_env *envlist)
{
    char **tabtab;
    t_env *tmp;
    int i;

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
	int		is_ok;
    int     if_is_ok;

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

int parent_process(int *fd, t_cmd *cmdlist)
{
    t_data *data;

    data = get_data();
    close(fd[1]);
    if (cmdlist->infile >= 0)
        close(cmdlist->infile);
    if (cmdlist->infile == -2)
        cmdlist->infile = fd[0];
    if (cmdlist->next != NULL && cmdlist->next->infile == -2)
        cmdlist->next->infile = fd[0];
    else
        close(fd[0]);
    return (data->error);
}

static void redir_in_out(t_cmd *list, int *fd)
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

void not_builtin_child(t_cmd *list, t_env *envlist, t_path *pathlist, int *pipefd)
{
    char *path;
    char **tabtab;

    path = NULL;
    redir_in_out(list, pipefd);
    if (checkpath(pathlist, list->cmd_arg[0], &path))
    {
        tabtab = lst_to_tabtab(envlist);
        execve(path, list->cmd_arg, tabtab);
    }
    if (path)
        free(path);
    signal(SIGINT, SIG_DFL);
}

void  ft_embouchure(t_cmd *cmdlist, t_token *list, t_env *envlist, t_path *pathlist, int *pipefd)
{
    int check;
    
    check = double_check(pathlist, cmdlist->cmd_arg[0]);
    if (is_builtin(cmdlist->cmd_arg[0]) == 1)
    {
        redir_builtin(cmdlist, pipefd);
        built(list, cmdlist, envlist, pathlist);
    }
    else if (is_builtin(cmdlist->cmd_arg[0]) == 0 && check == 0)
        not_builtin_child(cmdlist, envlist, pathlist, pipefd);
    else if (check == 1)
        free_cmd(&cmdlist);
    free_export_exec();
    ft_token_lstclear(&list);
    free_all_fork(cmdlist, pathlist, pipefd, envlist);
}

int heredoc_handler(char *str, t_env *envlist, int fd)
{
    char *line;

    while (1)
    {
        line = readline(">");
        if (!line)
        {
            write(2, "bash :warning: here-document delimited by end-of-file (wanted `", 64);
            write(2, str, ft_strlen(str));
            write(2, "`)\n", 3);
            close(fd);
            return (0);
        }
        if (ft_strcmp(line, str) == 0)
            break;
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

int here_doc(t_env *envlist, char *str)
{
    int fd;

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

int ft_redir(t_token *list, t_cmd *cmdlist, t_env *envlist)
{
    t_token *tmp;
    t_cmd *cmd;

    cmd = cmdlist;
    tmp = list;
    while (tmp) //! faudrait ptet parcourir t_cmd plutot que t_token
    {
        if (tmp->type == INPUT)
        {
            if (cmd->infile >= 0)
                close(cmd->infile);
            cmd->infile = open(tmp->next->token, O_RDONLY);
        }
        if (tmp->type == HEREDOC)
        {
            if (cmd->infile >= 0)
                close(cmd->infile);
            cmd->infile = here_doc(envlist, tmp->next->token);
        }
        while (cmd->next != NULL)
            cmd = cmd->next;
        if (tmp->type == TRUNC)
        {
            if (cmd->outfile >= 0)
                close(cmd->outfile);
            cmd->outfile = open(tmp->next->token, O_CREAT | O_RDWR | O_TRUNC, 0644);
        }
        if (tmp->type == APPEND)
        {
            if (cmd->outfile >= 0)
                close(cmd->outfile);
            cmd->outfile = open(tmp->next->token, O_CREAT | O_RDWR | O_APPEND, 0644);
        }
        tmp = tmp->next;
    }
    return (0);
}

static void ft_wait(t_cmd *cmdlist, t_token *token)
{
    int status;
    int len_cmd;
    t_data *list;
    t_cmd *tmp;
    int pid;

    list = get_data();
    len_cmd = len_cmdblocks(token);
    tmp = cmdlist;
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

static int exec_cmd(t_cmd *cmdlist, t_env *envlist, t_path *pathlist, t_token *list, int *pipefd)
{
    t_data *data;

    data = get_data();
    data->pid = fork();
    if (data->pid < 0)
        return (1);
    else if (!data->pid)
    {
        if (cmdlist->cmd_arg && cmdlist->cmd_arg[0])
            ft_embouchure(cmdlist, list, envlist, pathlist, pipefd);
        else
            free_all_fork(cmdlist, pathlist, pipefd, envlist);
    }
    else
        parent_process(pipefd, cmdlist);
    return (0);
}

int ft_exec(t_token *list, t_env *envlist, t_path *pathlist)
{
    t_cmd *cmdlist;
    t_cmd *tmp;
    t_data *data;
    int pipefd[2];

    data = get_data();
    data->pid = 0;
    pipefd[0] = -1;
    pipefd[1] = -1;
    cmdlist = token_to_cmd(list);
    tmp = cmdlist;
    if (!tmp)
        return (1);
    ft_redir(list , tmp, envlist);
    if (tmp && tmp->cmd_arg[0] && tmp->next == NULL && is_builtin(tmp->cmd_arg[0]) == true)
        return (built(list, tmp, envlist, pathlist));
    // if (pipe(pipefd) == -1)
    // {
    //     free_cmd(&cmdlist);
    //     return (1);
    // }
    // exec_cmd(cmdlist, envlist, pathlist, list, pipefd);
    // tmp = tmp->next;
    while (tmp)
    {
        if (pipe(pipefd) == -1)
        {
            free_cmd(&cmdlist);
            return (1);
        }
        exec_cmd(tmp, envlist, pathlist, list, pipefd);
        tmp = tmp->next;
    }
    // free_cmd(&tmp);
    ft_wait(cmdlist, list);
    free_cmd(&cmdlist);
    return (0);
}
