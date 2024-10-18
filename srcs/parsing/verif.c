/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:36:09 by ylouvel           #+#    #+#             */
/*   Updated: 2024/10/18 18:17:53 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parsing(char *str[])
{
	if (str)
	{
		if (ft_strcmp(str[0], "echo") == 0)
			echo(str);
		if (ft_strcmp(str[0], "cd") == 0)
			printf("cd\n");
		if (ft_strcmp(str[0], "pwd") == 0)
			printf("pwd\n");
		if (ft_strcmp(str[0], "unset") == 0)
			printf("unset\n");
		if (ft_strcmp(str[0], "exit") == 0)
			printf("exit si y'a un nombre/lettre mais un message different\n");
	}
	return (0);
}

void	for_one_word(char *str)
{
	if (ft_strcmp(str, "echo") == 0)
		echo_for_one_caractere(str);
	if (ft_strcmp(str, "pwd") == 0)
		printf("pwd\n");
	if (ft_strcmp(str, "cd") == 0)
		printf("cd 1\n");
	if (ft_strcmp(str, "env") == 0)
		print_env();
	if (ft_strcmp(str, "exit") == 0)
		ft_exit();
}

int	verif_word(char *str[])
{
	if (str[0])
	{
		if (ft_strcmp(str[0], "echo") == 0)
			return (0);
		if (ft_strcmp(str[0], "cd") == 0)
			return (0);
		if (ft_strcmp(str[0], "unset") == 0)
			return (0);
		if (ft_strcmp(str[0], "env") == 0)
			return (0);
		if (ft_strcmp(str[0], "exit") == 0)
			return (0);
		if (ft_strcmp(str[0], "pwd") == 0 || ft_strcmp(str[0], "export") == 0
			|| ft_strcmp(str[0], "env") == 0 || ft_strcmp(str[0], "exit") == 0
			|| ft_strcmp(str[0], "unset") == 0 || ft_strcmp(str[0], "cd") == 0
			|| ft_strcmp(str[0], "echo") == 0)
			printf("minishell: %s: command not found...\n", str[0]);
	}
	return (1);
}
