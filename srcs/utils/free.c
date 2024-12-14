/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:58:53 by ylouvel           #+#    #+#             */
/*   Updated: 2024/12/14 15:13:50 by ylouvel          ###   ########.fr       */
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

void	ft_env_lstclear(t_env **lst)
{
	t_env	*tmp;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		if ((*lst)->name)
			free((*lst)->name);
		if ((*lst)->value)
			free((*lst)->value);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

void	free_all(t_token *list, t_env *env, t_path *path)
{
	t_export	*export;
	t_data *data;

	data = get_data();
	export = get_export();
	if (data && data->input)
		free(data->input);
	if (export && export->content)
		free_tabtab(export->content);
	free_cmd();
	ft_token_lstclear(&list);
	ft_env_lstclear(&env);
	if(path)
		ft_free_path(path);
	rl_clear_history();
}

void ft_free_path(t_path *path)
{
    t_path *tmp;

    while (path)
    {
        tmp = path;
        path = path->next;
        free(tmp->name);
        free(tmp);
    }
	path = NULL;
}
