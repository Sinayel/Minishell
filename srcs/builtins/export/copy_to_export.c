/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_to_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:48:13 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/27 19:02:58 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

//! a ajouter dans le .h
char	**copy_env_export(char **env_export, int new_size)
{
	char	**temp;
	int		i;

	temp = (char **)malloc(sizeof(char *) * (new_size + 1));
	if (!temp)
		return (NULL);
	i = 0;
	while (env_export && env_export[i])
	{
		temp[i] = ft_strdup(env_export[i]);
		if (!temp[i])
		{
			free_tabtab(temp);
			return (NULL);
		}
		i++;
	}
	temp[i] = NULL;
	return (temp);
}

char	**add_to_env(char **temp, char *arg, int current_size)
{
	temp[current_size] = ft_strdup(arg);
	if (!temp[current_size])
	{
		free_tabtab(temp);
		return (NULL);
	}
	temp[current_size + 1] = NULL;
	return (temp);
}

char	**append_to_export(char **env_export, char *arg)
{
	int		current_size;
	char	**temp;
	char	**sorted;

	current_size = get_tab_size(env_export);
	temp = copy_env_export(env_export, current_size + 1);
	if (!temp)
		return (NULL);
	temp = add_to_env(temp, arg, current_size);
	if (!temp)
		return (NULL);
	sorted = sort_env_export(temp);
	if (!sorted)
	{
		free_tabtab(temp);
		return (NULL);
	}
	free_tabtab(env_export);
	return (sorted);
}

char	**sort_env_export(char **env_export)
{
	int		i;
	char	*temp;
	char	**env_export_sorted;

	i = 0;
	temp = NULL;
	if (env_export == NULL)
		return (NULL);
	env_export_sorted = env_export;
	while (env_export_sorted[i] && env_export_sorted[i + 1])
	{
		if (ft_strcmp(env_export_sorted[i], env_export_sorted[i + 1]) > 0)
		{
			temp = env_export_sorted[i];
			env_export_sorted[i] = env_export_sorted[i + 1];
			env_export_sorted[i + 1] = temp;
			i = 0;
		}
		else
			i++;
	}
	return (env_export_sorted);
}

void	print_export_line(char *env_entry)
{
	int	is_open_quote;
	int	j;

	is_open_quote = 0;
	j = 0;
	if (env_entry[0])
		printf("export ");
	while (env_entry[j])
	{
		printf("%c", env_entry[j]);
		if (env_entry[j] == '=' && is_open_quote == 0)
		{
			printf("\"");
			is_open_quote = 1;
		}
		if (!env_entry[j + 1] && is_open_quote == 1)
			printf("\"");
		j++;
	}
	printf("\n");
}
