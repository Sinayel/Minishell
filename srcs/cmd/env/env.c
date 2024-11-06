/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 20:39:47 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/06 19:12:18 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	free_env_vars(t_env *head)
{
	t_env	*temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->name);
		free(temp->value);
		free(temp);
	}
}

t_env	*env_import(char **envp)
{
	t_env	*env_list;
	int		i;
	char	*env_entry;
	char	*delimiter;
	char	*name;
	char	*value;

	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		env_entry = envp[i];
		delimiter = ft_strchr(env_entry, '=');
		if (delimiter != NULL)
		{
			*delimiter = '\0';
			name = env_entry;
			value = delimiter + 1;
			append_env_var(&env_list, name, value);
			*delimiter = '=';
			i++;
		}
	}
	return (env_list);
}
