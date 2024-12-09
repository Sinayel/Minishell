/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:21:47 by ylouvel           #+#    #+#             */
/*   Updated: 2024/12/09 20:39:14 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_too_many_arguments(t_token *list, t_data *data)
{
	if (list && list->next && list->next->next->type == ARG)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		data->error = 1;
		return (2);
	}
	return (0);
}

int	handle_invalid_argument(char *arg, t_token *list, t_env *env, t_path *path)
{
	printf("exit: %s: ", arg);
	ft_putstr_fd("numeric argument required\n", 2);
	free_all(list, env, path);
	exit(2);
}

long	parse_exit_code(char *arg, t_token *list, t_env *env, t_path *path)
{
	long	exit_code;

	exit_code = ft_strtol(arg, NULL, 10);
	if (exit_code < INT_MIN || exit_code > INT_MAX)
		handle_invalid_argument(arg, list, env, path);
	return ((unsigned char)exit_code);
}

int	ft_exit(t_token *list, t_env *env, t_path *path)
{
	t_data	*data;
	long	exit_code;
	int		result;
	char	*arg;

	data = get_data();
	exit_code = 0;
	result = handle_too_many_arguments(list, data);
	if (result)
		return (result);
	if (list && list->next)
	{
		arg = list->next->token;
		if (!is_valid_number(arg) && list->next->type != ARG)
			handle_invalid_argument(arg, list, env, path);
		exit_code = parse_exit_code(arg, list, env, path);
	}
	free_all(list, env, path);
	printf("exit\n");
	exit(exit_code);
	return (2);
}
