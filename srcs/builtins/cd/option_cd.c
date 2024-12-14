/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:56:46 by ylouvel           #+#    #+#             */
/*   Updated: 2024/12/14 21:43:43 by judenis          ###   ########.fr       */
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
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": not set\n", 2);
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
		ft_putstr_fd("bash: cd: HOME not set\n", 2);
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
		{
			ft_putstr_fd("bash: cd: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd(": Not a directory\n", 2);
		}
		if (errno == ENOENT)
		{
			ft_putstr_fd("bash: cd: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
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
			ft_putstr_fd("bash: cd: OLDPWD not set\n", 2);
			data->error = 1;
			return (0);
		}
		printf("%s\n", path);
		return (0);
	}
	return (1);
}
