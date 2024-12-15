/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 14:18:54 by ylouvel           #+#    #+#             */
/*   Updated: 2024/12/15 14:33:17 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	print_error(char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
	return (true);
}

int	print_numeric(char **args, t_token *list, t_env *env, t_path *path)
{
	print_error("exit: ");
	print_error(args[0]);
	print_error(": numeric argument required\n");
	free_all(list, env, path);
	free_tabtab(args);
	return (2);
}

int	print_too_many(t_data *data, char **args)
{
	print_error("exit: too many arguments\n");
	free_tabtab(args);
	data->error = 1;
	return (1);
}
