/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:58:53 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/28 16:28:57 by ylouvel          ###   ########.fr       */
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
	ft_token_lstclear(&list);
	ft_free_path(path);
	if (data && data->input)
		free(data->input);
}

void	free_token(t_token **token)
{
	t_token	*current;
	t_token	*next;

	current = *token;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*token = NULL;
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
