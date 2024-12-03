/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:48:59 by ylouvel           #+#    #+#             */
/*   Updated: 2024/12/03 14:58:40 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	print_all_exports(char **env_export)
{
	int	i;

	i = 0;
	while (env_export && env_export[i])
	{
		print_export_line(env_export[i]);
		i++;
	}
}

void	printf_export(char **env_export)
{
	if (!env_export || !env_export[0])
		return ;
	print_all_exports(env_export);
}

char	*pipeline_to_env_value(t_env *envlist, char *name)
{
	char	*value;
	char	**split_name;
	t_env	*temp;

	value = NULL;
	split_name = NULL;
	if (!name || !envlist)
		return (NULL);
	if (check_equal_arg(name) == 1)
		split_name = ft_split(name, '=');
	else
		split_name = ft_split(name, ' ');
	if (!split_name || !split_name[0])
		return (NULL);
	temp = envlist;
	value = return_env_value(temp, split_name[0]);
	free_tabtab(split_name);
	return (value);
}

t_export	*get_export(void)
{
	static t_export	export;

	return (&export);
}

int	contains_equal(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			return (1);
		i++;
	}
	return (0);
}
