/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:58:53 by ylouvel           #+#    #+#             */
/*   Updated: 2024/12/13 22:43:23 by judenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_valid_number(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

void	free_all(t_token *list, t_env *env, t_path *path)
{
	t_export	*export;
	t_data		*data;

	data = get_data();
	export = get_export();
	if (export && export->content)
		free_tabtab(export->content);
	ft_env_lstclear(&env);
	free_cmd(&data->cmd);
	ft_token_lstclear(&list);
	ft_free_path(path);
	if (data && data->input)
		free(data->input);
}

void	ft_free_path(t_path *path)
{
	t_path	*temp;

	if (!path)
		return ;
	while (path)
	{
		temp = path->next;
		free(path->name);
		free(path);
		path = temp;
	}
	path = NULL;
}
