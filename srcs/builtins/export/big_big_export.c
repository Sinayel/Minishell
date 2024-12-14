/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_big_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:50:55 by ylouvel           #+#    #+#             */
/*   Updated: 2024/12/14 21:52:59 by judenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_strlen_tabtab_gpt(char **split_arg)
{
	int	i;
	int	j;
	int	v;

	i = 0;
	j = 0;
	v = 0;
	while (split_arg[i])
	{
		if (i != 0)
			v++;
		j = 0;
		while (split_arg[i][j])
		{
			v++;
			j++;
		}
		i++;
	}
	return (v);
}

void	handle_valid_argument(t_env *env_list, t_export *export, char *arg,
		char *env_value)
{
	char	**split_arg;

	if (check_equal_arg(arg) == 1)
	{
		split_arg = ft_split(arg, '=');
		if (env_value == NULL)
			process_new_export(env_list, export, arg, split_arg);
		else
			process_existing_export(env_list, export, env_value, split_arg);
		free_tabtab(split_arg);
	}
	else if (should_append_to_export(export, arg, env_value))
		export->content = append_to_export(export->content, arg);
}

void	handle_invalid_identifier(t_data *data, char *arg)
{
	ft_putstr_fd("bash: export: '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	data->error = 1;
}

void	process_arguments(t_env *env_list, t_export *export, t_data *data,
		char **arg_tabtab)
{
	int		i;
	char	*env_value;

	i = 0;
	while (arg_tabtab[i])
	{
		env_value = pipeline_to_env_value(env_list, arg_tabtab[i]);
		if (is_env_name_valid(arg_tabtab[i]) == 1)
			handle_invalid_identifier(data, arg_tabtab[i]);
		else
			handle_valid_argument(env_list, export, arg_tabtab[i], env_value);
		i++;
	}
}

char	**split_arguments(char *arg)
{
	char	**arg_tabtab;

	if (!arg)
		return (NULL);
	if (cmb_word(arg) > 1)
		return (ft_split(arg, ' '));
	arg_tabtab = (char **)malloc(sizeof(char *) * 2);
	if (!arg_tabtab)
		return (NULL);
	arg_tabtab[0] = ft_strdup(arg);
	arg_tabtab[1] = NULL;
	return (arg_tabtab);
}
