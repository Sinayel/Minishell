/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:16:17 by ylouvel           #+#    #+#             */
/*   Updated: 2024/10/08 20:42:05 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"
#include <stdio.h>

//! ◦ CD with only a relative or absolute path |  (JULIO)
//! ◦ PWD with no options                      |  (JULIO)
//! ◦ UNSET with no options                    |  (JULIO)
//! ◦ EXPORT with no options                   |  (YANNS)
//! ◦ ENV with no options or arguments         |  (YANNS)
//! ◦ EXIT                                     |  (YANNS)

void	init_variable(int argc, char **argv)
{
	t_data *data = get_data();
	(void)argc;
	(void)argv;
	data->env = NULL;
	data->str = NULL;
	data->input = NULL;
	data->cmd = NULL;
	data->status = 0;
}

t_data *get_data(void)
{
	static t_data data;
	return (&data);
}

int	main(int argc, char **argv, char **env)
{
	t_data *data = get_data();
	init_variable(argc, argv);
	data->env = env;
	while (1)
	{
		data->input = readline("minishell$ ");
		data->str = ft_split(data->input);
		if (word_count(data->input) == 1)
		{
			for_one_word(data->str[0]);
		}
		else if (verif_word(data->str) == 0 && data->str[1] != NULL)
			parsing(data->str);
		if (*data->input)
			add_history(data->input);
		ft_free(data->str);
		free(data->input);
	}
	rl_clear_history();
	return (0);
}