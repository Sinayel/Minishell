/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:47:37 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/27 18:48:01 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

//! a ajouter dans le .h
char	*ft_magouilles(char *str1, char *str2, char *str3)
{
	char	*dest;
	int		v;

	dest = ft_magouilles_v2(str1, str2, str3);
	if (!dest)
		return (NULL);
	v = 0;
	v = copy_string(dest, str1, v);
	v = copy_string(dest, str2, v);
	v = copy_string(dest, str3, v);
	dest[v] = '\0';
	return (dest);
}

char	**env_to_export(t_env *env_list)
{
	char	**env_export;
	int		len;
	int		i;
	t_env	*temp;

	temp = env_list;
	i = 0;
	len = cmb_env(temp);
	env_export = (char **)malloc(sizeof(char *) * (len + 1));
	if (!env_export)
		return (NULL);
	while (temp)
	{
		env_export[i] = ft_magouilles(temp->name, "=", temp->value);
		temp = temp->next;
		i++;
	}
	env_export[i] = NULL;
	env_export = sort_env_export(env_export);
	return (env_export);
}

int	check_equal_arg(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (1);
	while (arg[i])
	{
		if (arg[i] == '=' && !arg[i + 1])
			return (2);
		if (arg[i] == '=' && arg[i + 1] != '\0')
			return (1);
		i++;
	}
	return (0);
}

char	**replace_export(char **env_export, char **split_arg)
{
	int	i;

	i = 0;
	while (env_export[i])
	{
		if (ft_strncmp(env_export[i], split_arg[0],
				ft_strlen(split_arg[0])) == 0)
		{
			free(env_export[i]);
			env_export[i] = ft_magouilles(split_arg[0], "=", split_arg[1]);
			return (env_export);
		}
		i++;
	}
	return (env_export);
}

int	get_tab_size(char **tab)
{
	int	size;

	size = 0;
	while (tab && tab[size])
		size++;
	return (size);
}
