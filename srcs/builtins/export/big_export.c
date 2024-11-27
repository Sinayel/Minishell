/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:50:18 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/27 18:50:39 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	**replace_one_in_export(char **export, char *arg)
{
	int		i;
	char	**split_arg;
	char	*sous_str;

	i = 0;
	sous_str = NULL;
	split_arg = ft_split(arg, '=');
	while (export[i])
	{
		sous_str = ft_substr(export[i], 0, len_before_space(export[i]));
		if (ft_strcmp(sous_str, split_arg[0]) == 0)
		{
			free(export[i]);
			export[i] = ft_strdup(arg);
		}
		free(sous_str);
		i++;
	}
	free_tabtab(split_arg);
	return (export);
}

void	init_export(t_export *export_list, t_env *envlist)
{
	if (!export_list->content)
		export_list->content = env_to_export(envlist);
}

int	should_append_to_export(t_export *export, char *arg, char *env_value)
{
	return ((check_equal_arg(arg) == 0 || check_equal_arg(arg) == 2)
		&& env_value == NULL && verif_if_in_export(export->content, arg) == 0);
}

void	process_existing_export(t_env *env_list, t_export *export,
		char *env_value, char **split_arg)
{
	export->content = replace_export(export->content, split_arg);
	if (ft_strcmp(env_value, split_arg[0]) != 0)
		replace_env_value(&env_list, split_arg);
}

void	process_new_export(t_env *env_list, t_export *export, char *arg,
		char **split_arg)
{
	if (verif_if_in_export(export->content, arg) == 1)
		export->content = replace_one_in_export(export->content, arg);
	else
		export->content = append_to_export(export->content, arg);
	export_to_env(&env_list, split_arg);
}
