/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:27:53 by judenis           #+#    #+#             */
/*   Updated: 2024/10/07 20:27:55 by judenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

//! ◦ CD with only a relative or absolute path |  (JULIO)
//! ◦ PWD with no options                      |  (JULIO)
//! ◦ UNSET with no options                    |  (JULIO)
//! ◦ EXPORT with no options                   |  (YANNS)
//! ◦ ENV with no options or arguments         |  (YANNS)
//! ◦ EXIT                                     |  (YANNS)

int	parsing(char *str[])
{
	int	i;

	i = 0;
	if (str[i])
	{
		if (ft_strcmp(str[0], "echo") == 0)
			echo(str);
		if (ft_strcmp(str[0], "cd") == 0)
			printf("cd\n");
		if (ft_strcmp(str[0], "pwd") == 0)
			printf("pwd\n");
		if (ft_strcmp(str[0], "unset") == 0)
			printf("unset\n");
		if (ft_strcmp(str[0], "env") == 0)
			printf("env\n");
		if (ft_strcmp(str[0], "exit") == 0)
			printf("exit\n");
	}
	return (0);
}

int	verif_input(char *input)
{
	int	i;

	i = 0;
	// printf("%s \n", input);
	
	while (input[i])
	{
		if (input[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}
