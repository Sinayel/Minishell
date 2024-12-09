/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:46:10 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/27 18:47:17 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

//! a ajouter dans le .h
void	replace_env_value_ez(t_env **env_list, char *name, char *arg)
{
	t_env	**temp;

	if (*env_list == NULL || env_list == NULL)
		return ;
	temp = env_list;
	while (*temp)
	{
		if (ft_strcmp((*temp)->name, name) == 0)
		{
			free((*temp)->value);
			(*temp)->value = ft_strdup(arg);
			return ;
		}
		*temp = (*temp)->next;
	}
}

void	replace_env_value(t_env **env_list, char **arg)
{
	t_env	**temp;

	if (*env_list == NULL || env_list == NULL)
		return ;
	temp = env_list;
	while (*temp)
	{
		if (ft_strcmp((*temp)->name, arg[0]) == 0)
		{
			free((*temp)->value);
			(*temp)->value = ft_strdup(arg[1]);
			return ;
		}
		*temp = (*temp)->next;
	}
}

int	cmb_env(t_env *envlist)
{
	t_env	*temp;
	int		len;

	len = 0;
	temp = envlist;
	while (temp)
	{
		if (temp->name)
			len++;
		temp = temp->next;
	}
	return (len);
}

char	*ft_magouilles_v2(char *str1, char *str2, char *str3)
{
	size_t	total_len;
	char	*dest;

	total_len = ft_strlen(str1) + ft_strlen(str2) + ft_strlen(str3) + 1;
	dest = (char *)malloc(sizeof(char) * total_len);
	return (dest);
}

int	copy_string(char *dest, char *src, int v)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[v] = src[i];
		v++;
		i++;
	}
	return (v);
}
