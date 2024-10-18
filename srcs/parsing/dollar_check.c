/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:47:15 by ylouvel           #+#    #+#             */
/*   Updated: 2024/10/18 18:25:29 by ylouvel          ###   ########.fr       */
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
