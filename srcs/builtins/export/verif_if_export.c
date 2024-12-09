/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_if_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:49:40 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/27 18:49:58 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*extract_prefix(char *export_line)
{
	return (ft_substr(export_line, 0, len_before_space(export_line)));
}

int	compare_export(char *sous_str, char **split_arg, char *arg)
{
	if (split_arg)
	{
		if (ft_strcmp(sous_str, split_arg[0]) == 0)
			return (1);
	}
	else if (ft_strcmp(sous_str, arg) == 0)
		return (1);
	return (0);
}

char	**split_argument(char *arg)
{
	if (contains_equal(arg))
		return (ft_split(arg, '='));
	return (NULL);
}

int	check_export(char **export, char **split_arg, char *arg)
{
	int		i;
	char	*sous_str;

	i = 0;
	while (export[i])
	{
		sous_str = extract_prefix(export[i]);
		if (compare_export(sous_str, split_arg, arg))
		{
			free(sous_str);
			return (1);
		}
		free(sous_str);
		i++;
	}
	return (0);
}

int	verif_if_in_export(char **export, char *arg)
{
	char	**split_arg;
	int		result;

	if (!export)
		return (0);
	split_arg = split_argument(arg);
	result = check_export(export, split_arg, arg);
	free_tabtab(split_arg);
	return (result);
}
