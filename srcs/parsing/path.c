/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:04:59 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/06 19:37:35 by ylouvel          ###   ########.fr       */
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
	while (path_breaker[i])
	{
		path = add_env(path, path_breaker[i]);
		i++;
	}
	return (path);
}

int	double_check(t_path *path, t_token *tmp)
{
	char	*word;
	int		fd;

	while (path)
	{
		word = ft_strjoin(path->name, "/");
		word = ft_strjoin(word, tmp->token);
		fd = open(word, O_RDONLY);
		if (fd > 0)
		{
			printf("Dans ta petite mere <3\n");
			close(fd);
			return (0);
		}
		path = path->next;
	}
	close(fd);
	return (1);
}
