/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:16:14 by ylouvel           #+#    #+#             */
/*   Updated: 2024/10/07 20:54:58 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_string(char *str[])
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			write(1, &str[i][j], 1);
			j++;
		}
		if (str[i][j] == '\0' && str[i + 1] != NULL)
		{
			write(1, " ", 1);
		}
		i++;
	}
}

void	print_string_with_option(char *str[])
{
	int	i;
	int	j;

	i = 2;
	j = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			write(1, &str[i][j], 1);
			j++;
		}
		if (str[i][j] == '\0' && str[i + 1] != NULL)
		{
			write(1, " ", 1);
		}
		i++;
	}
}

int	echo_for_one_caractere(char *input)
{
	if (ft_strcmp(input, "echo") == 0)
		printf("\n");
	return (0);
}

int	echo(char *str[])
{
	if (ft_strcmp(str[1], "-n") == 0 && str != NULL)
		print_string_with_option(str);
	else if (ft_strcmp(str[1], "-n") != 0 && str != NULL)
	{
		print_string(str);
		printf("\n");
	}
	return (0);
}
