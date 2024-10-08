/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 20:41:12 by ylouvel           #+#    #+#             */
/*   Updated: 2024/10/08 20:45:44 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// Fonctions echo
void	print_string(char *str[])
{
	int	i;

	i = 1;
	while (str[i])
	{
		write(1, str[i], strlen(str[i]));
		if (str[i + 1] != NULL)
		{
			write(1, " ", 1);
		}
		i++;
	}
}

void	print_string_with_option(char *str[])
{
	int	i;

	i = 2;
	while (str[i])
	{
		write(1, str[i], strlen(str[i]));
		if (str[i + 1] != NULL)
		{
			write(1, " ", 1);
		}
		i++;
	}
}

int	echo_for_one_caractere(char *input)
{
	if (strcmp(input, "echo") == 0)
	{
		printf("\n");
	}
	return (0);
}

int	echo(char *str[])
{
	if (strcmp(str[1], "-n") == 0 && str != NULL)
	{
		print_string_with_option(str);
	}
	else if (str != NULL)
	{
		print_string(str);
		printf("\n");
	}
	return (0);
}