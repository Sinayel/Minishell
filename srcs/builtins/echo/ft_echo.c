/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:43:50 by ylouvel           #+#    #+#             */
/*   Updated: 2024/12/14 19:33:52 by judenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	echo(t_token *list, t_cmd *cmd)
{
	(void)list;
	t_cmd *tmp;
	t_data	*data;
	int i;

	i = 1;
	data = get_data();
	tmp = cmd;
	while (tmp->cmd_arg[i])
	{
		ft_putstr_fd(tmp->cmd_arg[i], 1);
		if (tmp->cmd_arg[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	// 	if (ft_strcmp(tmp->token, "echo") == 0)
	// 		break ;
	// 	tmp = tmp->next;
	// }
	// if (tmp->next)
	// 	tmp = tmp->next;
	// while (cmd)
	// {
	// 	if (tmp->type == INPUT || tmp->type == HEREDOC || tmp->type == APPEND || tmp->type == TRUNC)
	// 	{
	// 		if (tmp->next->type == ARG)
	// 			tmp = tmp->next;
	// 		tmp = tmp->next;
	// 		continue;
	// 	}
		// if (tmp->type == PIPE)
		// 	break ;
		// printf("%s", tmp->token);
		// if (tmp->next)
		// 	printf(" ");
		// tmp = tmp->next;
	printf("\n");
	data->error = 0;
	return (0);
}
