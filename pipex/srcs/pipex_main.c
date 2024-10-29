/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:15:04 by judenis           #+#    #+#             */
/*   Updated: 2024/10/29 18:43:32 by judenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int 	ft_strchr(const char *s, int c)
{
	while ((*s != '\0') && (*s != c))
	{
		s++;
	}
	if (*s == c)
	{
		return (0);
	}
	return (1);
}

void relative_path(char **split_cmd, char **env)
{
	if (execve(split_cmd[0], split_cmd, env) == -1)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(split_cmd[0] , 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(0);
	}
}

void	ft_exec(char *cmd, char **env)
{
	char	**split_cmd;
	char	*path;

	split_cmd = ft_split(cmd, ' ');
	if (ft_strchr(split_cmd[0], '/') == 0)
	{
		path = NULL;
		relative_path(split_cmd, env);
	}
	else
	{
		path = get_path(split_cmd[0], env);
		if (execve(path, split_cmd, env) == -1)
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(split_cmd[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			ft_free_tab(split_cmd);
			exit(0);
		}	
	}
}

void	here_doc_put_in(char *here_doc, int *p_fd)
{
	char	*ret;

	close(p_fd[0]);
	while (1)
	{
		ret = get_next_line(0);
		if (ft_strncmp(ret, here_doc, ft_strlen(here_doc)) == 0)
		{
			free(ret);
			exit(0);
		}
		ft_putstr_fd(ret, p_fd[1]);
		free(ret);
	}
}

void	here_doc(char *here_doc)
{
	int		p_fd[2];
	pid_t	pid;

	if (pipe(p_fd) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (!pid)
		here_doc_put_in(here_doc, p_fd);
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
		wait(NULL);
	}
}

void	do_pipe(char *cmd, char **env)
{
	pid_t	pid;
	int		p_fd[2];

	if (pipe(p_fd) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (!pid)
	{
		close(p_fd[0]);
		dup2(p_fd[1], 1);
		ft_exec(cmd, env);
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
	}
}

// void	pipex(t_token *list, char **env)
// {
// 	int	i;
// 	int	fd_in;
// 	int	fd_out;

// 	if (ac < 5)                                      //!
// 		exit_handler(1, NULL);                       //!
// 	if (ft_strcmp(av[1], "here_doc") == 0)
// 	{
// 		if (ac < 6)                                  //!   
// 			exit_handler(1, NULL);					 //!
// 		i = 3;
// 		fd_out = open_file(av[ac - 1], 1);
// 		here_doc(av);
// 	}
// 	else
// 	{
// 		i = 2;
// 		fd_in = open_file(av[1], 0); //!  A VERIFIER SI LE FICHIER EXISTE
// 		fd_out = open_file(av[ac - 1], 1); //!  A VERIFIER SI LE FICHIER EXISTE
// 		dup2(fd_in, 0);
// 	}
// 	while (i < ac - 2)
// 		do_pipe(av[i++], env);
// 	dup2(fd_out, 1);								//! L'OUVERTURE/DUPLICATION DU FD N'EST PAS VERIFIE
// 	ft_exec(av[ac - 2], env);
// }

// int	main(void)             //* DIFFERENCIER LES ERREURS SI C'EST SOIT UN CHEMIN ABSOLU/RELATIF OU UN COMMANDE LITTERALE (NO SUCH FILE / COMMAND NOT FOUND)
// {
// 	pipex(t_token *list, char **env);
// 	return (0);
// }

void	pipex(t_token *list, char **env)
{
	int fd_in = 0;
	int fd_out = 0;
    while (list)
    {
        if (list->type == 1) // INPUT
        {
            fd_in = open_file(list->next->token, 0);
            list = list->next->next;
        }
        else if (list->type == 2) // HEREDOC
        {
            here_doc(list->next->token);
            list = list->next->next;
        }
        else if (list->type == 3) // TRUNC
        {
            fd_out = open_file(list->next->token, 1);
            list = list->next->next;
        }
        else if (list->type == 4) // APPEND
        {
            fd_out = open_file(list->next->token, 2);
            list = list->next->next;
        }
        else if (list->type == 5) // PIPE
        {
            do_pipe(list->next->token, env);
            list = list->next->next;
        }
        else if (list->type == 6) // CMD
        {
            do_pipe(list->token, env);
            list = list->next;
        }
        else if (list->type == 7) // ARG
        {
            do_pipe(list->token, env);
            list = list->next;
        }
    }
	if (fd_out != 0 && fd_out != -1)
		close(fd_out);
	if (fd_in != 0 && fd_in != -1)
		close(fd_in);
}

int main(int ac, char **av, char **env) 
{
    (void)ac;
    (void)av;
    t_token *list;
    list = malloc(sizeof(t_token));
	list->next = malloc(sizeof(t_token));
	list->next->next = malloc(sizeof(t_token));
	list->next->next->next = malloc(sizeof(t_token));
	list->next->next->next->next = malloc(sizeof(t_token));
    list->token = "cat";
    list->type = 6;
    list->i = 0;
    list = list->next;
    list->token = "Makefile";
    list->type = 7;
    list->i = 1;
    list = list->next;
    list->token = "|";
    list->type = 5;
    list->i = 2;
    list = list->next;
    list->token = "grep";
    list->type = 6;
    list->i = 3;
    list = list->next;
    list->token = "=";
    list->type = 7;
    list->i = 4;
    list->next = NULL;
    pipex(list, env);    
}

//! Verifier si la commande est un builtin ou non
//! Si l'infile n'est pas trouve, la deuxieme commande s'execute quand meme et celles qui suivent aussi
//! Si la commande donnee est un repertoire, le mess d'erreur doit etre "Is a directory"
//! UN NOMBRE NON NEGLIGEABLE DE FD NE SONT PAS FERMES