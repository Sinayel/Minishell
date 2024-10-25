/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 20:42:21 by ylouvel           #+#    #+#             */
/*   Updated: 2024/10/25 18:47:22 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_list(t_data *head)
{
	t_data	*temp;

	temp = head;
	while (temp != NULL)
	{
		printf("%s -> ", temp->value);
		temp = temp->next;
	}
	printf("NULL\n");
}

void	ft_lstclear(t_data **lst)
{
	t_data	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->value); //1 Libere `value` du noeud actuel
		free(*lst);          //1 Libere le noeud actuel
		*lst = temp;
	}
	*lst = NULL;
}

t_data	*add_last(t_data *list, char *value)
{
	t_data	*new_element;
	t_data	*temp;

	new_element = malloc(sizeof(t_data));
	if (!new_element)
		return (list);
	new_element->value = strdup(value);
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

t_data *init_list(t_data *list)
{
    t_data *data = get_data();
    int i = 0;
    while (data->first_split[i])
    {
        list = add_last(list, data->first_split[i]);
        i++;
    }
    return list;
}
