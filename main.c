/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:16:17 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/07 13:35:58 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

//! ◦ CD with only a relative or absolute path |  (JULIO)
//! ◦ PWD with no options                      |  (JULIO)
//! ◦ UNSET with no options                    |  (JULIO)
//! ◦ PIPEX							             |  (JULIO)
//! ◦ ENV with no options or arguments         |  (JULIO)
//! ◦ ECHO                                     |  (JULIO)
//! ◦ EXIT                                     |  (JULIO)
//! ◦ EXPORT with no options                   |  (YANS)
//! ◦ PARSING (99% du projet)                  |  (YANS)

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
	(void)argc;
	(void)argv;
	data->input = NULL;
}

int	main(int argc, char *argv[], char **env)
{
	t_token	*list;
	t_data	*data;
	t_env	*env_list;

	list = NULL;
	env_list = NULL;
	data = get_data();
	init_variable(argc, argv);
	while (1)
	{
		data->input = readline("Minishell> ");
		list = tokenization(data->input);
		if (list)
			parsing(list, env_list = env_import(env), data);
		// list = remove_quote(list);
		if (*data->input)
			add_history(data->input);
		print_list(list);
		ft_token_lstclear(&list);
		if (data->input)
			free(data->input);
	}
	return (0);
}
