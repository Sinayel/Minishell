/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_big_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:50:55 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/27 18:51:17 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
	printf("bash: export: `%s': not a valid identifier\n", arg);
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
