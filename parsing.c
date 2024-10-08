/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:27:53 by judenis           #+#    #+#             */
/*   Updated: 2024/10/08 19:41:17 by judenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

//! ◦ CD with only a relative or absolute path |  (JULIO)
//! ◦ PWD with no options                      |  (JULIO)
//! ◦ UNSET with no options                    |  (JULIO)
//! ◦ EXPORT with no options                   |  (YANNS)
//! ◦ ENV with no options or arguments         |  (YANNS)
//! ◦ EXIT                                     |  (YANNS)

int	parsing(void)
{
	t_data	*data = get_data();
	int	i;

	i = 0;
	if (data->str[i])
	{
		if (ft_strcmp(data->str[0], "echo") == 0)
			printf("echo\n");
		if (ft_strcmp(data->str[0], "cd") == 0)
			printf("cd\n");
		if (ft_strcmp(data->str[0], "pwd") == 0)
			ft_pwd();
		if (ft_strcmp(data->str[0], "unset") == 0)
			printf("unset\n");
		if (ft_strcmp(data->str[0], "env") == 0)
			printf("env\n");
		if (ft_strcmp(data->str[0], "export") == 0)
			printf("export\n");
		if (ft_strcmp(data->str[0], "exit") == 0)
			ft_exit();
	}
	return (0);
}
