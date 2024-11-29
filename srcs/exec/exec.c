/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:07:14 by judenis           #+#    #+#             */
/*   Updated: 2024/11/29 16:43:32 by judenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
    if (ft_strcmp(str, "cd") || ft_strcmp(str, "pwd") == 0 || ft_strcmp(str, "unset") == 0 || ft_strcmp(str, "env") == 0 || ft_strcmp(str, "echo") == 0 || ft_strcmp(str, "exit") == 0 || ft_strcmp(str, "export") == 0)
		return true;
    return false;
}

void print_cmd(t_cmd *list)
{
    t_cmd *tmp;

    tmp = list;
    int i = 0;
    int len = 0;
    while (tmp)
    {
        i = 0;
        while (tmp->cmd_arg[i])
        {
            printf("noeud n.%d = [%s]\n", len, tmp->cmd_arg[i]);
            i++;
        }
        len++;
        tmp = tmp->next;
    }
}

t_cmd *token_to_cmd(t_token *list)
{
    t_token *tmp = list;
    t_cmd *cmd_head = NULL;
    t_cmd *cmd_tail = NULL;
    int i;

    while (tmp)
    {
        if (tmp->type == CMD)
        {
            // Création d'un nouveau nœud de commande
            t_cmd *new_cmd = malloc(sizeof(t_cmd));
            if (!new_cmd)
                return (NULL); // Gestion des erreurs d'allocation mémoire
            new_cmd->next = NULL;

            // Comptage des arguments nécessaires
            int arg_count = len_in_block(tmp);

            // Allocation pour les arguments (commande incluse)
            new_cmd->cmd_arg = malloc(sizeof(char *) * (arg_count + 1));
            if (!new_cmd->cmd_arg)
            {
                free(new_cmd);
                return (NULL);
            }

            // Copie de la commande et des arguments
            i = 0;
            while (tmp && (tmp->type == CMD || tmp->type == ARG))
            {
                new_cmd->cmd_arg[i] = ft_strdup(tmp->token);
                if (!new_cmd->cmd_arg[i])
                {
                    // Libération en cas d'échec
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

            // Ajout à la liste chaînée des commandes
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

	while (pathlist)
	{
		*path = ft_magouilles(pathlist->name, "/", cmd);
		is_ok = access(*path, X_OK | X_OK | X_OK);
		if (is_ok == 0)
		{
			return (true);
		}
		pathlist = pathlist->next;
	}
	return (false);
}

void parent_process()
{
    int status;
    wait(&status);
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    return (1);
}

void child_process(t_cmd *list, t_env *envlist, int *pipfd, t_path *pathlist)
{
    char *path;
    char **tabtab;
    path = NULL;
    if (check_path(pathlist, list->cmd_arg[0], &path))
    {
        tabtab = lst_to_tabtab(envlist);
        execve(path, list->cmd_arg, tabtab);
        free(tabtab);
    }
    if (path)
        free(path);
    ft_exit(NULL, envlist, pathlist);
}

int exec_not_builtin(t_cmd *list, t_env *envlist, t_path *pathlist)
{
    t_cmd *tmp;
    int pipfd[2];
    pid_t pid;

    tmp = list;
    pipfd[0] = 0;
    pipfd[1] = 0;
    while (tmp)
    {
        if (is_builtin(tmp->cmd_arg[0]) == false)
        {
            pid = fork();
            if (pid < 0)
            {
                perror("fork");
                return (1);
            }
            else if (!pid)
                child_process(tmp, envlist, pipfd, pathlist);
            else
                parent_process();
        }
    }
}

int heredoc_handler(char *str, t_env *envlist, int fd)
{
    char *line;

    while (1)
    {
        line = readline(">");
        if (!line)
        {
            write(2, "bash :warning: here-document delimited by end-of-file (wanted `", 61);
            write(2, str, ft_strlen(str));
            write(2, "`)\n", 3);
            break;
        }
        if (ft_strcmp(line, str) == 0)
            break;
        line = proccess_dollar_value(line, envlist);
        write(fd, line, ft_strlen(line));
        write(fd, "\n", 1);
        free(line);
    }
    free(line);
    close(fd);
    return (0);
}

int here_doc(t_env *envlist, char *str)
{
    int fd;

    fd = open(".tmp_heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (fd < 0)
        return (-1);
    if (!heredoc_handler(str, envlist, fd))
    {
        unlink(".tmp_heredoc");
        return (-1);
    }
    fd = open(".tmp_heredoc", O_RDONLY);
    if (fd > 0)
        unlink(".tmp_heredoc");
    return (fd);
}

int is_redir_heredoc(t_token *list, t_cmd *cmdlist, t_env *envlist)
{
    t_token *tmp;
    int i;
    int fd;

    i = 0;
    tmp = list;
    fd = 0;
    while (tmp) //! faudrait ptet parcourir t_cmd plutot que t_token
    {
        if (tmp->type == INPUT)
        {
            if (cmdlist->infile >= 0)
                close(cmdlist->infile);
            fd = open(tmp->next->token, O_RDONLY);
        }
        if (tmp->type == HEREDOC) //* ce serait coolos si ca checkait aussi TRUNC ou APPEND
        {
            if (cmdlist->infile >= 0)
                close(cmdlist->infile);
            fd = here_doc(envlist, tmp->next->token);
        }
        tmp = tmp->next;
    }
    return (fd);
}

int ft_exec(t_token *list, t_env *envlist, t_path *pathlist)
{
    t_cmd *cmdlist;
    int pipfd[2];
    
    pipfd[0] = 0;
    pipfd[1] = 0;
    cmdlist = token_to_cmd(list);
    is_redir_heredoc(list , cmdlist, envlist);
    if (!cmdlist)
        return (1);
    if (!is_builtin(cmdlist->cmd_arg[0]))
        return (exec_not_builtin(cmdlist, envlist, pathlist));
    else
        return (cmd(cmdlist->cmd_arg[0], list, envlist, pathlist));
}