/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:47:15 by ylouvel           #+#    #+#             */
/*   Updated: 2024/10/11 20:23:04 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	msg_dollar(const char *before, const char *env_var)
{
	t_data	*data;
	char	*env_value;

	data = get_data();
	env_value = get_env(env_var, data->env);
	if (env_value != NULL && before != NULL)
		printf("minishell: %s%s: unknow command...", before, env_value);
	else if (env_value)
		printf("minishell: %s: unknow command...", env_value);
	else
		printf("minishell: $: unknow command...");
}

char	*dollar_check(char **before, char **env_var)
{
	t_data	*data;
	char	*dollar_pos;

	data = get_data();
	if (data->input == NULL)
		return (NULL);
	dollar_pos = strchr(data->input, '$');
	if (dollar_pos != NULL)
	{
		*before = strndup(data->input, dollar_pos - data->input);
		*env_var = strdup(dollar_pos + 1);
		msg_dollar(*before, *env_var);
		return (*env_var);
	}
	return (NULL);
}
