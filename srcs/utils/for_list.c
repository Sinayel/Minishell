/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:10:13 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/26 11:45:02 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_token_lstclear(t_token **lst)
{
	t_token	*temp;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->token);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}

void ft_env_lstclear(t_env **lst)
{
    t_env *tmp;

    if (!lst || !*lst)
        return;

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

t_path	*add_env(t_path *list, char *value)
{
	t_path	*new_element;
	t_path	*temp;

	new_element = malloc(sizeof(t_path));
	if (!new_element)
		return (list);
	new_element->name = value;
	new_element->next = NULL;
	if (list == NULL)
		return (new_element);
	temp = list;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_element;
	return (list);
}

t_token	*add_last(t_token *list, char *value)
{
	t_token	*new_element;
	t_token	*temp;

	new_element = malloc(sizeof(t_token));
	if (!new_element)
		return (list);
	new_element->token = value;
	new_element->type = 0;
	new_element->first = 0;
	new_element->next = NULL;
	new_element->prev = NULL;
	if (!list)
		return (new_element);
	temp = list;
	while (temp->next)
		temp = temp->next;
	temp->next = new_element;
	new_element->prev = temp;
	return (list);
}
