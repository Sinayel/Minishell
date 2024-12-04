/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:43:50 by ylouvel           #+#    #+#             */
/*   Updated: 2024/12/04 18:45:32 by ylouvel          ###   ########.fr       */
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
	while (tmp && tmp->type == ARG)
	{
		printf("%s", tmp->token);
		if (tmp->next)
			printf(" ");
		tmp = tmp->next;
	}
	printf("\n");
	data->error = 0;
	return (0);
}
