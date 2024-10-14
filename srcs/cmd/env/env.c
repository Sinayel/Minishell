/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 20:39:47 by ylouvel           #+#    #+#             */
/*   Updated: 2024/10/11 20:22:29 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*get_env(const char *var, char **env)
{
	int		i;
	size_t	len;

	i = 0;
	len = strlen(var);
	while (env[i])
	{
		if (strncmp(env[i], var, len) == 0 && env[i][len] == '=')
		{
			return (env[i] + len + 1);
		}
		i++;
	}
	return (NULL);
}

void	print_env(void)
{
	t_data	*data;
	int		i;

	data = get_data();
	i = 0;
	if (data->env != NULL)
	{
		while (data->env[i] != NULL)
		{
			printf("%s\n", data->env[i]);
			i++;
		}
	}
}
