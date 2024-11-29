/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:45:29 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/29 17:35:58 by judenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

//! a ajouter dans le .h
t_env	*create_new_env(char *name)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = ft_strdup(name);
	new->value = ft_strdup("");
	new->next = NULL;
	return (new);
}

void	append_to_value(t_env *new, char **arg)
{
	char	*temp;
	int		i;

	temp = NULL;
	i = 1;
	while (arg[i])
	{
		if (i > 1)
			temp = ft_magouilles(new->value, "=", arg[i]);
		else
			temp = ft_strjoin(new->value, arg[i]);
		free(new->value);
		new->value = temp;
		i++;
	}
}

void	add_to_env_list(t_env **env_list, t_env *new)
{
	t_env	*current;

	current = *env_list;
	if (!current)
	{
		*env_list = new;
		return ;
	}
	while (current->next)
		current = current->next;
	current->next = new;
}

void	export_to_env(t_env **env_list, char **arg)
{
	t_env	*new;

	if (!arg || !arg[0])
		return ;
	new = create_new_env(arg[0]);
	if (!new)
		return ;
	append_to_value(new, arg);
	add_to_env_list(env_list, new);
}

int	is_env_name_valid(char *name)
{
	int	i;

	i = 0;
	if ((name[0] >= '0' && name[0] <= '9') || name[0] == '=')
		return (1);
	while (name[i])
	{
		if ((name[i] >= 32 && name[i] < 47) || (name[i] >= 58 && name[i] < 61)
			|| (name[i] >= 62 && name[i] < 65) || (name[i] >= 91
				&& name[i] < 95) || name[i] == 96 || name[i] >= 123)
			return (1);
		i++;
	}
	return (0);
}
