/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_check_dollar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 20:23:59 by ylouvel           #+#    #+#             */
/*   Updated: 2024/10/11 20:24:23 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	write_env_var(char **str, char **env)
{
	t_data	*data;

	data = get_data();
	data->var_end = *str + 1;
	while (*data->var_end && (isalnum(*data->var_end) || *data->var_end == '_'))
		data->var_end++;
	data->var_name = strndup(*str, data->var_end - *str);
	data->env_value = get_env(data->var_name, env);
	free(data->var_name);
	if (data->env_value)
		write(1, data->env_value, strlen(data->env_value));
	else
		write(1, "$", 1);
	*str = data->var_end;
}

void	print_with_vars(char *str, char **env)
{
	t_data	*data;

	data = get_data();
	data->dollar_pos = strchr(str, '$');
	while (data->dollar_pos)
	{
		write(1, str, data->dollar_pos - str);
		str = data->dollar_pos + 1;
		if (*str)
			write_env_var(&str, env);
		data->dollar_pos = strchr(str, '$');
	}
	write(1, str, strlen(str));
}
