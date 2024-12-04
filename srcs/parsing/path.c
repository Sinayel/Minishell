/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:04:59 by ylouvel           #+#    #+#             */
/*   Updated: 2024/12/04 19:04:59 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_path	*return_path(t_env *env)
{
	t_path	*path;
	char	*tmp;
	char	**path_breaker;
	int		i;

	path_breaker = NULL;
	path = NULL;
	i = 0;
	tmp = return_env_value(env, "PATH");
	if (tmp == NULL)
		return (NULL);
	if (tmp)
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
	if (path_breaker)
		free(path_breaker);
	return (path);
}

void	errno_check(char *token)
{
	t_data	*data;

	data = get_data();
	if (errno == EACCES)
	{
		printf("%s: ", token);
		ft_putstr_fd("Permission denied\n", 2);
	}
	else if (errno == EISDIR)
	{
		printf("%s: ", token);
		ft_putstr_fd("Is a directory\n", 2);
	}
	else
	{
		printf("%s: ", token);
		ft_putstr_fd("Command not found\n", 2);
	}
	data->error = 126;
}

int	double_check(t_path *path, t_token *tmp, char *input)
{
	char	*word;
	char	*temp;
	int		is_ok;
	int		is_if_ok;

	if (tmp->token[0] != '\0')
	{
		while (path)
		{
			temp = ft_strjoin(path->name, "/");
			word = ft_strjoin(temp, tmp->token);
			free(temp);
			is_if_ok = access(input, X_OK | X_OK | X_OK);
			is_ok = access(word, X_OK | X_OK | X_OK);
			if (is_ok == 0 || is_if_ok == 0)
			{
				free(word);
				return (0);
			}
			free(word);
			path = path->next;
		}
	}
	return (1);
}
