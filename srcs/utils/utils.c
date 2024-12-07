/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 20:42:21 by ylouvel           #+#    #+#             */
/*   Updated: 2024/12/07 21:42:03 by judenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_export(t_export *export)
{
	if (export->content)
		free_tabtab(export->content);
	free(export);
}

void free_tabtab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return;
	while (tab && tab[i])
		free(tab[i++]);
	if (tab)
		free(tab);
	tab = NULL;
}

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

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
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

