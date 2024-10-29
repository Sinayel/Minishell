/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:16:17 by ylouvel           #+#    #+#             */
/*   Updated: 2024/10/29 14:39:41 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

//! ◦ CD with only a relative or absolute path |  (JULIO)
//! ◦ PWD with no options                      |  (JULIO)
//! ◦ UNSET with no options                    |  (JULIO)
//! ◦ PIPEX					                   |  (JULIO)
//! ◦ EXPORT with no options                   |  (YANS)
//! ◦ ENV with no options or arguments         |  (YANS)
//! ◦ ECHO                                     |  (YANS)
//! ◦ EXIT                                     |  (YANS)
//! ◦ PARSING                                  |  (YANS)

//! UNIQUEMENT POUR LES STRUCTURE (NE MARCHE PAS AVEC LES LISTE CHAINEE)
t_data *get_data(void)
{
	static t_data data;
	return (&data);
}

void	init_variable(int argc, char **argv, char **env)
{
	t_data *data = get_data();
	(void)argc;
	(void)argv;
	data->env = env;
	data->input = NULL;
}

int	main(void)
{
	t_token	*list;
	t_data	*data;

	list = NULL;
	data = get_data();
	while (1)
	{
		data->input = readline("Minishell> ");
		if(data->input)
			list = tokenization(data->input);

        if (*data->input)
			add_history(data->input);

        print_list(list);

		ft_token_lstclear(&list);             //1 Libere tous les noeud de ma liste
		free(data->input);
	}
	return (0);
}
