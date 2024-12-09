/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:48:40 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/28 15:48:57 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	unset_export(char *arg)
{
	int			i;
	int			j;
	char		**dest;
	char		*sous_str;
	t_export	*export;

	j = 0;
	export = get_export();
	sous_str = NULL;
	dest = NULL;
	dest = malloc_dest(export, dest);
	if (!dest)
		return ;
	i = 0;
	while (export->content[i])
	{
		sous_str = ft_substr(export->content[i], 0,
				len_before_space(export->content[i]));
		if (ft_strcmp(sous_str, arg) != 0)
			dest[j++] = ft_strdup(export->content[i]);
		free(sous_str);
		i++;
	}
	dest = return_dest(dest, export, j);
	export->content = dest;
}

void	free_and_update_env_list(t_env **env_list, t_env **prev,
		t_env **current, t_env *next)
{
	if (*prev == NULL)
		*env_list = next;
	else
		(*prev)->next = next;
	free_name_and_value(*current);
	*current = next;
}

void	process_env_node(t_env **env_list, t_env **current, t_env **prev,
		char *arg)
{
	t_env	*next;

	next = (*current)->next;
	if (ft_strcmp((*current)->name, arg) == 0)
		free_and_update_env_list(env_list, prev, current, next);
	else
	{
		*prev = *current;
		*current = next;
	}
}

void	iterate_env_list(t_env **env_list, char **arg_split, int *i)
{
	t_env	*temp;
	t_env	*prev;

	temp = *env_list;
	prev = NULL;
	while (temp)
		process_env_node(env_list, &temp, &prev, arg_split[*i]);
	(*i)++;
}

void	while_arg_split(int *i, t_env **env_list, char **arg_split)
{
	if (!*env_list)
	{
		free_tabtab(arg_split);
		return ;
	}
	iterate_env_list(env_list, arg_split, i);
}
