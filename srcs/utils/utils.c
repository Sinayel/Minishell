/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 20:42:21 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/06 19:41:15 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if (!s1)
		return (1);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

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

void	ft_del_one_token(t_token *lst)
{
	if (!lst)
		return ;
	if (lst->prev)
	{
		if (lst->next)
			lst->next->prev = lst->prev;
		else
			lst->prev->next = NULL;
	}
	if (lst->next)
	{
		if (lst->prev)
			lst->prev->next = lst->next;
		else
			lst->next->prev = NULL;
	}
	free(lst->token);
	free(lst);
}

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
	if (list == NULL)
		return (new_element);
	temp = list;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_element;
	new_element->prev = temp;
	return (list);
}
