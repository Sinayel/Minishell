/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 20:42:21 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/07 18:13:29 by ylouvel          ###   ########.fr       */
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

    if (!lst || !*lst)  // Vérification si la liste est déjà NULL
        return;

    while (*lst)
    {
        tmp = (*lst)->next;
        
        // Libération des éléments de l'environnement
        if ((*lst)->name)  // Vérification si name est non NULL
            free((*lst)->name);
        if ((*lst)->value)  // Vérification si value est non NULL
            free((*lst)->value);
        
        free(*lst);  // Libération de l'élément lui-même
        *lst = tmp;  // Avance au prochain élément
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
	if (list == NULL)
		return (new_element);
	temp = list;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_element;
	return (list);
}
