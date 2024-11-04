/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:15:04 by judenis           #+#    #+#             */
/*   Updated: 2024/10/29 20:47:49 by judenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_token_lstclear(t_token **lst)
{
	t_token	*temp;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		if ((*lst)->token)
			free((*lst)->token); //1 Libere `value` du noeud actuel
		free(*lst);          //1 Libere le noeud actuel
		*lst = temp;
	}
	*lst = NULL;
}

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

void	do_pipe(char *cmd, char *arg, char **env)
{
	pid_t	pid;
	int		p_fd[2];
	char *cmd_join;

	if (pipe(p_fd) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (!pid)
	{
		close(p_fd[0]);
		dup2(p_fd[1], 1); 
		if (arg != NULL)
		{
			printf("test ?\n");
			cmd_join = ft_strjoin(cmd, " ");
			cmd_join = ft_strjoin(cmd_join, arg);
			ft_exec(cmd_join, env);
		}
		//? ft_join pour essayer de changer le moins de truc posssible ?
		else
			ft_exec(cmd, env);
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
	}
	// if (cmd_join)
	// 	free(cmd_join);
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

int cmb_cmd(t_token *list)
{
	int i = 0;
	while (list)
	{
		if (list->type == 6)
			i++;
		list = list->next;
	}
	return i;
}

void	pipex(t_token *list, char **env)
{
	int nb_cmd = cmb_cmd(list);
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
            fd_out = open_file(list->next->token, 1);
            list = list->next->next;
        }
        else if (list->type == 5 && list->next->type == 6 && list->next->next->type == 7) // PIPE
        {
            do_pipe(list->next->token, list->next->next->token, env);
            list = list->next->next->next;
        }
		else if (list->type == 5 && list->next->type == 6) // PIPE
        {
            do_pipe(list->next->token, NULL, env);
            list = list->next->next;
        }
        else if (list->type == 6 && list->next->type == 7) // CMD
        {
            do_pipe(list->token, list->next->token, env);
            list = list->next->next;
        }
		else if (list->type == 6) // CMD
        {
            do_pipe(list->token, NULL, env);
            list = list->next;
        }
        else if (list->type == 7) // ARG
        {
            list = list->next;
        }
		else
			printf("Error\n");
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
	t_token *list = NULL;
	t_token *current = NULL;

	// Helper function to create a new token node
	t_token *create_token(char *token, int type, int index) {
		t_token *new_token = malloc(sizeof(t_token));
		if (!new_token)
			return NULL;
		new_token->token = token;
		new_token->type = type;
		new_token->i = index;
		new_token->next = NULL;
		return new_token;
	}

	// Create and link the tokens
	list = create_token("cat", 6, 0);
	current = list;
	current->next = create_token("Makefile", 7, 1);
	current = current->next;
	current->next = create_token("|", 5, 2);
	current = current->next;
	current->next = create_token("grep", 6, 3);
	current = current->next;
	current->next = create_token("=", 7, 4);
    pipex(list, env);
	return (0);    
}

//! Verifier si la commande est un builtin ou non
//! Si l'infile n'est pas trouve, la deuxieme commande s'execute quand meme et celles qui suivent aussi
//! Si la commande donnee est un repertoire, le mess d'erreur doit etre "Is a directory"
//! UN NOMBRE NON NEGLIGEABLE DE FD NE SONT PAS FERMES