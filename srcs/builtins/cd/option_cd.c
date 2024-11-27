/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:56:46 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/27 17:57:30 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*cd_handle_dollar(t_env *env_list, char *input)
{
	char	*name;
	char	*path;

	name = ft_substr(input, 1, ft_strlen(input) - 1);
	path = return_env_value(env_list, name);
	if (!path)
	{
		printf("bash: cd: %s not set\n", name);
		free(name);
		return (NULL);
	}
	free(name);
	return (path);
}

int	no_home_set(char *path, t_data *data)
{
	if (!path)
	{
		printf("bash: cd: HOME not set\n");
		data->error = 1;
		return (0);
	}
	return (1);
}

void	mouv_cd(char *path, t_env *env_list, t_data *data)
{
	char	*initial_path;

	initial_path = ft_strdup(path);
	if (access(path, X_OK) == 0)
		ch_oldpwd(&env_list);
	if (chdir(initial_path) != 0)
	{
		if (errno == ENOTDIR)
			printf("bash: cd: %s: Not a directory\n", path);
		if (errno == ENOENT)
			printf("bash: cd: %s: No such file or directory\n", path);
		else
			perror("chdir");
		data->error = 1;
	}
	free(initial_path);
	ch_pwd(&env_list);
}

int	bad_option(char *input, t_data *data)
{
	if (input[0] == '-' && input[1] == '-')
	{
		printf("bash: cd: --: invalid option\n");
		data->error = 2;
		return (0);
	}
	if (input[0] == '-' && input[1] != '-' && input[1] != '\0')
	{
		printf("bash: cd: -%c: invalid option\n", input[1]);
		data->error = 2;
		return (0);
	}
	return (1);
}

int	option_for_cd_(char *input, t_data *data, t_env *env_list, char *path)
{
	if (input[0] == '-' && input[1] == '\0')
	{
		path = return_env_value(env_list, "OLDPWD");
		if (!path)
		{
			printf("bash: cd: OLDPWD not set\n");
			data->error = 1;
			return (0);
		}
		printf("%s\n", path);
		return (0);
	}
	return (1);
}
