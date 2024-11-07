/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:08:59 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/07 18:05:03 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_env	*create_env_var(char *name, char *value)
{
	t_env	*new_node;

	if (!name || !value)
		return (NULL);
	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
	{
		perror("Erreur d'allocation de mémoire");
		exit(EXIT_FAILURE);
	}
	new_node->name = ft_strdup(name);
	if (!new_node->name)
	{
		free(new_node);
		perror("Erreur strdup name");
		exit(EXIT_FAILURE);
	}
	new_node->value = ft_strdup(value);
	if (!new_node->value)
	{
		free(new_node->name);
		free(new_node);
		perror("Erreur strdup value");
		exit(EXIT_FAILURE);
	}
	new_node->next = NULL;
	return (new_node);
}

void	append_env_var(t_env **head, char *name, char *value)
{
	t_env	*new_node;
	t_env	*temp;

	new_node = create_env_var(name, value);
	if (*head == NULL)
		*head = new_node;
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}
}

void	print_env_vars(t_env *head, char *name)
{
	t_env	*temp;

	temp = head;
	while (temp)
	{
		if (ft_strcmp(temp->name, name) == 0)
			printf("%s=%s\n", temp->name, temp->value);
		temp = temp->next;
	}
}

char	*return_env_value(t_env *head, char *name)
{
	t_env	*temp;

	temp = head;
	while (temp)
	{
		if (ft_strcmp(temp->name, name) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}
