/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:16:17 by ylouvel           #+#    #+#             */
/*   Updated: 2024/12/13 19:49:29 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

//! ◦ PIPEX									   |  (JULIO)  98%
//! ◦ UNSET with no options                    |  (JULIO) [V]
//! ◦ EXPORT with no options                   |  (JULIO) [V]
//! ◦ CD with only a relative or absolute path |  (JULIO) [V]
//! ◦ PWD with no options                      |  (JULIO) [V]
//! ◦ ENV with no options or arguments         |  (JULIO) [V]
//! ◦ EXIT                                     |  (YANS)  [V]
//! ◦ ECHO                                     |  (YANS)  [V]
//! ◦ PID									   |  (YANS)  [V]
//! ◦ PARSING (99% du projet)                  |  (YANS)  [V]

t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
}

void	init_variable(int argc, char **argv, t_env *env)
{
	t_data		*data;
	t_export	*export;

	export = get_export();
	init_export(export, env);
	data = get_data();
	data->pid = 4242;
	data->error = 0;
	data->input = NULL;
	(void)argc;
	(void)argv;
	signals();
}

bool	exit_shell(t_data *data, t_env *env, t_token *list)
{
	t_export	*export;

	if (!data->input)
	{
		printf("exit\n");
		free(data->input);
		export = get_export();
		if (export && export->content)
			free_tabtab(export->content);
		ft_token_lstclear(&list);
		ft_env_lstclear(&env);
		exit(0);
		return (false);
	}
	return (true);
}

int	main(int argc, char *argv[], char **env)
{
	t_token	*list;
	t_data	*data;
	t_env	*env_list;

	list = NULL;
	data = get_data();
	env_list = env_import(env);
	init_variable(argc, argv, env_list);
	while (1)
	{
		data->input = readline("Minishell> ");
		if (!exit_shell(data, env_list, list))
			break ;
		list = tokenization(data->input, env_list);
		if (list)
		{
			add_history(data->input);
			parsing_exec(list, env_list, data);
		}
		print_list(list);
		ft_token_lstclear(&list);
		if (data->input)
			free(data->input);
	}
	return (0);
}
