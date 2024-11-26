/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 20:46:28 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/26 18:20:19 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

//! FINI
int len_before_space(char *arg)
{
    int len;

    len = 0;
    while (arg[len] && arg[len] != '=')
        len++;
    return (len);
}

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

void	while_arg_split(int *i, t_env *temp, char **arg_split, t_env **env_list,
		t_env *prev)
{
	t_env	*next;

	temp = *env_list;
	if (!temp)
		return (free_tabtab(arg_split));
	prev = NULL;
	while (temp)
	{
		next = temp->next;
		if (ft_strcmp(temp->name, arg_split[*i]) == 0)
		{
			if (prev == NULL)
				*env_list = next;
			else
				prev->next = next;
			free_name_and_value(temp);
			temp = next;
		}
		else
		{
			prev = temp;
			temp = next;
		}
	}
	(*i)++;
}

int	ft_unset(t_env **env_list, char *arg)
{
	t_env	*temp;
	t_env	*prev;
	char	**arg_split;
	int		i;

	temp = NULL;
	prev = NULL;
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
		while_arg_split(&i, temp, arg_split, env_list, prev);
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
