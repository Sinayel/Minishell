/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:04:59 by ylouvel           #+#    #+#             */
/*   Updated: 2024/12/03 16:59:16 by judenis          ###   ########.fr       */
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
	path_breaker = ft_split_for_path(tmp, ':');
	if(!path_breaker)
	{
		free(tmp);
		return NULL;
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

void errno_check(char *token)
{
	printf("\n\nerrno = %d\n\n\n", errno);
	t_data *data;
	data = get_data();
	if (errno == EACCES)
	{
		printf("%s: ", token);
		ft_putstr_fd("Permission denied\n", 2);
		data->error = 126;
	}
	else if (errno == EISDIR)
	{
		printf("%s: ", token);
		ft_putstr_fd("Is a directory\n", 2);
		data->error = 126;
	}
	else
	{
		printf("%s: ", token);
		ft_putstr_fd("Command not found\n", 2);
		data->error = 127;
	}
}

int		double_check(t_path *path, t_token *tmp, char *input)
{
	// t_data *data;
	char	*word;
	char	*temp;
	int		is_ok;
	int 	if_is_ok;

	// data = get_data();
	while (path)
	{
		temp = ft_strjoin(path->name, "/");
		word = ft_strjoin(temp, tmp->token);
		free(temp);
		if_is_ok = access(input, X_OK);
		is_ok = access(word, X_OK);
		if (path->next == NULL && is_ok != 0)
			errno_check(tmp->token);
		if (is_ok == 0 || if_is_ok == 0)
		{
			free(word);
			return (0);
		}
		free(word);
		path = path->next;
	}
	return (1);
}
