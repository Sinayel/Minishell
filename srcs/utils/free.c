/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:58:53 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/13 15:12:28 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(t_token *list, t_data *data, t_env *env, t_path *path)
{
	ft_env_lstclear(&env);
	ft_token_lstclear(&list);
	ft_free_path(path);
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

void ft_free_path(t_path *path)
{
    t_path *temp;
    if(!path)
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
