/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:04:59 by ylouvel           #+#    #+#             */
/*   Updated: 2024/12/15 14:27:05 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_path	*return_path(t_env *env)
{
	t_path	*path;
	char	*tmp;
	char	**path_breaker;
	int		i;

	path = NULL;
	i = 0;
	tmp = return_env_value(env, "PATH");
	if (!tmp)
		return (NULL);
	path_breaker = ft_split_for_path(tmp, ':');
	if (!path_breaker)
	{
		free(tmp);
		return (NULL);
	}
	while (path_breaker[i])
	{
		path = add_env(path, path_breaker[i]);
		i++;
	}
	i = 0;
	free(path_breaker);
	return (path);
}

void	errno_check(int err)
{
	t_data	*data;

	data = get_data();
	if (err == EACCES)
	{
		ft_putstr_fd(" Permission denied\n", 2);
		data->error = 126;
	}
	else
	{
		ft_putstr_fd(" command not found\n", 2);
		data->error = 127;
	}
}

int	is_directory(const char *path)
{
	struct stat	path_stat;

	return (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode));
}

int	check_access(char *path)
{
	if (access(path, X_OK) == -1)
	{
		if (errno == EISDIR || errno == EACCES)
		{
			if (path[0] == '.' || path[0] == '/')
			{
				errno_check(errno);
				return (3);
			}
		}
		return (2);
	}
	return (0);
}
