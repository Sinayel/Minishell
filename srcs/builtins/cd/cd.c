/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:43:37 by ylouvel           #+#    #+#             */
/*   Updated: 2024/12/07 22:16:13 by judenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*skip_spaces_input(char *input)
{
	int	i;

	i = 0;
	while (input[i] && (input[i] == ' ' || input[i] == '\t'))
		i++;
	return (input + i);
}

int	ft_cd(t_env *env_list, char *input)
{
	char	*path;
	t_data	*data;

	data = get_data();
	path = NULL;
	if (input == NULL || input[0] == '~' || (input[0] == '-' && input[1] == '-'
			&& input[2] == '\0'))
	{
		path = return_env_value(env_list, "HOME");
		if (no_home_set(path, data) == 0)
			return (0);
		mouv_cd(path, env_list, data);
	}
	else
	{
		path = NULL;
		if (bad_option(input, data) == 0)
			return (0);
		if (option_for_cd_(input, data, env_list, path) == 0)
			path = return_env_value(env_list, "OLDPWD");
		else
			path = input;
		mouv_cd(path, env_list, data);
	}
	return (0);
}

int	len_for_cd(t_token *list)
{
	t_token	*tmp;
	int		i;
	int		j;

	tmp = list;
	tmp = tmp->next;
	i = 0;
	j = 0;
	while (tmp && tmp->type > 5)
	{
		while (tmp->token[j])
		{
			i++;
			j++;
		}
		i++;
		j = 0;
		tmp = tmp->next;
	}
	return (i);
}

int	ft_arg_cd(t_env *env, t_token *list)
{
	int		len;
	t_token	*tmp;
	char	*value_for_cd;
	int		i;
	int		j;

	len = len_for_cd(list);
	tmp = list->next;
	if (len == 0)
		return (ft_cd(env, NULL));
	value_for_cd = (char *)malloc(sizeof(char) * (len + 1));
	init_var_i(&i, &j);
	while (tmp && tmp->type > 5)
	{
		while (tmp->token[j])
			value_for_cd[i++] = tmp->token[j++];
		if (tmp->next)
			value_for_cd[i++] = ' ';
		j = 0;
		tmp = tmp->next;
	}
	value_for_cd[i] = '\0';
	ft_cd(env, value_for_cd);
	free(value_for_cd);
	return (0);
}
