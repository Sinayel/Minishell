/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:13:58 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/06 19:07:22 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//? Pour enlever les doubles quotes des noeud de la liste chainee
t_token	*remove_quote(t_token *list)
{
	t_token	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = list;
	while (tmp)
	{
		if (tmp->type == CMD || tmp->type == ARG)
		{
			tmp->token = check_quote(tmp, &i, &j);
			i = 0;
			j = 0;
		}
		tmp = tmp->next;
	}
	return (list);
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
