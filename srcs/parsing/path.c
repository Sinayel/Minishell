/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:04:59 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/08 11:59:42 by ylouvel          ###   ########.fr       */
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
	path_breaker = ft_split(tmp, ':');
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

int	double_check(t_path *path, t_token *tmp)
{
	char	*word;
	char	*temp;
	int		is_ok;

	while (path)
	{
		temp = ft_strjoin(path->name, "/");
		word = ft_strjoin(temp, tmp->token);
		free(temp);
		is_ok = access(word, X_OK | X_OK | X_OK);
		if (is_ok == 0)
		{
			printf("Dans ta petite mere <3\n");
			free(word);
			return (0);
		}
		free(word);
		path = path->next;
	}
	return (1);
}
