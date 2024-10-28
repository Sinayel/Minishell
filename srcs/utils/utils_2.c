/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 20:42:21 by ylouvel           #+#    #+#             */
/*   Updated: 2024/10/28 18:33:00 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_list(t_token *list)
{
	t_token	*temp;

	temp = list;
	while (temp != NULL)
	{
		printf("[%d] %s -> ", temp->type, temp->token);
		temp = temp->next;
	}
	printf("NULL\n");
}

void	ft_token_lstclear(t_token **lst)
{
	t_token	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->token); //1 Libere `value` du noeud actuel
		free(*lst);          //1 Libere le noeud actuel
		*lst = temp;
	}
	*lst = NULL;
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
	new_element->next = NULL;
	if (list == NULL)
		return (new_element);
	temp = list;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_element;
	return (list);
}
