/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:48:51 by ylouvel           #+#    #+#             */
/*   Updated: 2024/12/07 22:14:09 by judenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_export(t_env *env_list, char *arg)
{
	t_export	*export;
	t_data		*data;
	char		**arg_tabtab;

	export = get_export();
	data = get_data();
	init_export(export, env_list);
	if (!export->content)
		return (0);
	if (!arg)
	{
		printf_export(export->content);
		return (0);
	}
	arg_tabtab = split_arguments(arg);
	process_arguments(env_list, export, data, arg_tabtab);
	free_tabtab(arg_tabtab);
	return (0);
}

int	ft_arg_export(t_env *env, t_token *list)
{
	int		len;
	t_token	*tmp;
	char	*value_for_export;
	int		i;
	int		j;

	len = len_for_cd(list);
	tmp = list->next;
	if (len == 0)
		return (ft_export(env, NULL));
	value_for_export = (char *)malloc(sizeof(char) * (len + 1));
	init_var_i(&i, &j);
	while (tmp && tmp->type > 5)
	{
		while (tmp->token[j])
			value_for_export[i++] = tmp->token[j++];
		if (tmp->next)
			value_for_export[i++] = ' ';
		j = 0;
		tmp = tmp->next;
	}
	value_for_export[i] = '\0';
	ft_export(env, value_for_export);
	free(value_for_export);
	return (0);
}
