/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:16:17 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/19 19:36:23 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

//! ◦ CD with only a relative or absolute path |  (JULIO) V
//! ◦ PWD with no options                      |  (JULIO) V
//! ◦ ENV with no options or arguments         |  (JULIO) V
//! ◦ PIPEX										 |  (JULIO) X
//! ◦ UNSET with no options                    |  (JULIO) X
//! ◦ EXPORT with no options                   |  (JULIO) X
//! ◦ EXIT                                     |  (YANS) V
//! ◦ ECHO                                     |  (YANS) X
//! ◦ PID											|  (YANS) X
//! ◦ PARSING (99% du projet)                  |  (YANS) X

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

//! UNIQUEMENT POUR LES STRUCTURE (NE MARCHE PAS AVEC LES LISTE CHAINEE)
t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
}

void	init_variable(int argc, char **argv)
{
	t_data	*data;

	data = get_data();
	data->pid = getpid();
	data->error = 0;
	data->input = NULL;
	(void)argc;
	(void)argv;
	signal(SIGINT, signal_handler);
}

bool	exit_shell(t_data *data, t_env *env)
{
	if (!data->input)
	{
		printf("exit\n");
		free(data->input);
		ft_env_lstclear(&env);
		return (false);
	}
	return (true);
}

void cleanup(t_data *data, t_env *env_list)
{
    if (data->input)
        free(data->input);
    ft_env_lstclear(&env_list);
    free(data); // Si data est alloué dynamiquement
}

int	main(int argc, char *argv[], char **env)
{
	t_token	*list;
	t_data	*data;
	t_env	*env_list;

	list = NULL;
	data = get_data();
	env_list = env_import(env);
	init_variable(argc, argv);
	while (1)
	{
		data->input = readline("Minishell> ");
		if (!exit_shell(data, env_list))
			break ;
		list = tokenization(data->input, env_list);
		if(data->input)
			add_history(data->input);
		if (list)
			parsing(list, env_list, data);
		// print_list(list);
		ft_token_lstclear(&list);
		if(data->input)
		{
			free(data->input);
			data->input = NULL;
		}
	}
	return (0);
}
