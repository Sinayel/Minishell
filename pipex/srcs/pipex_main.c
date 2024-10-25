/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:15:04 by judenis           #+#    #+#             */
/*   Updated: 2024/10/25 16:48:05 by judenis          ###   ########.fr       */
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

void	here_doc_put_in(char **av, int *p_fd)
{
	char	*ret;

	close(p_fd[0]);
	while (1)
	{
		ret = get_next_line(0);
		if (ft_strncmp(ret, av[2], ft_strlen(av[2])) == 0)
		{
			free(ret);
			exit(0);
		}
		ft_putstr_fd(ret, p_fd[1]);
		free(ret);
	}
}

void	here_doc(char **av)
{
	int		p_fd[2];
	pid_t	pid;

	if (pipe(p_fd) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (!pid)
		here_doc_put_in(av, p_fd);
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

void	pipex(int ac, char **av, char **env)
{
	int	i;
	int	fd_in;
	int	fd_out;

	if (ac < 5)                                      //!
		exit_handler(1, NULL);                       //!
	if (ft_strcmp(av[1], "here_doc") == 0)
	{
		if (ac < 6)                                  //!   
			exit_handler(1, NULL);					 //!
		i = 3;
		fd_out = open_file(av[ac - 1], 1);
		here_doc(av);
	}
	else
	{
		i = 2;
		fd_in = open_file(av[1], 0);
		fd_out = open_file(av[ac - 1], 1);
		dup2(fd_in, 0);
	}
	while (i < ac - 2)
		do_pipe(av[i++], env);
	dup2(fd_out, 1);								//! L'OUVERTURE/DUPLICATION DU FD N'EST PAS VERIFIE
	ft_exec(av[ac - 2], env);
}

int	main(int ac, char **av, char **env)             //! DIFFERENCIER LES ERREURS SI C'EST SOIT UN CHEMIN ABSOLU/RELATIF OU UN COMMANDE LITTERALE (NO SUCH FILE / COMMAND NOT FOUND)
{
	pipex(ac, av, env);
	return (0);
}
