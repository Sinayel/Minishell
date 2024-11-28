/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 20:46:28 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/28 15:48:33 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

//! FINI
int	len_before_space(char *arg)
{
	int	len;

	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	return (len);
}

int	ft_unset(t_env **env_list, char *arg)
{
	char	**arg_split;
	int		i;

	i = 0;
	if (cmb_word(arg) > 1)
		arg_split = ft_split(arg, ' ');
	else
	{
		arg_split = (char **)malloc(sizeof(char *) * 2);
		arg_split[0] = ft_strdup(arg);
		arg_split[1] = NULL;
	}
	while (arg_split[i])
		unset_export(arg_split[i++]);
	i = 0;
	while (arg_split[i])
	{
		while_arg_split(&i, env_list, arg_split);
	}
	free_tabtab(arg_split);
	return (0);
}

int	ft_arg_unset(t_env *env, t_token *list)
{
	int		len;
	t_token	*tmp;
	char	*value_for_unset;
	int		i;
	int		j;

	len = len_for_cd(list);
	tmp = list->next;
	if (len == 0)
		return (0);
	value_for_unset = (char *)malloc(sizeof(char) * (len + 1));
	init_var_i(&i, &j);
	while (tmp)
	{
		while (tmp->token[j])
			value_for_unset[i++] = tmp->token[j++];
		if (tmp->next)
			value_for_unset[i++] = ' ';
		j = 0;
		tmp = tmp->next;
	}
	value_for_unset[i] = '\0';
	ft_unset(&env, value_for_unset);
	free(value_for_unset);
	return (0);
}
