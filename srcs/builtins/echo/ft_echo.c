/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:43:50 by ylouvel           #+#    #+#             */
/*   Updated: 2024/12/14 18:06:55 by judenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	echo(t_token *list)
{
	t_token	*tmp;
	t_data	*data;

	data = get_data();
	tmp = list;
	while (tmp)
	{
		if (ft_strcmp(tmp->token, "echo") == 0)
			break ;
		tmp = tmp->next;
	}
	if (tmp->next)
		tmp = tmp->next;
	while (tmp)
	{
		if (tmp->type == INPUT || tmp->type == HEREDOC || tmp->type == APPEND || tmp->type == TRUNC)
		{
			if (tmp->next->type == ARG)
				tmp = tmp->next;
			tmp = tmp->next;
		}
		if (tmp->type == PIPE)
			break ;
		printf("%s", tmp->token);
		if (tmp->next)
			printf(" ");
		tmp = tmp->next;
	}
	printf("\n");
	data->error = 0;
	return (0);
}
