/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:43:50 by ylouvel           #+#    #+#             */
/*   Updated: 2024/12/14 21:21:46 by judenis          ###   ########.fr       */
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
	ft_putstr_fd("\n", 1);
	data->error = 0;
	return (0);
}
