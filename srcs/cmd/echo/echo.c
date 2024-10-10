/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 20:41:12 by ylouvel           #+#    #+#             */
/*   Updated: 2024/10/10 16:55:10 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// Fonctions echo
void	print_string(char *str[], char **env)
{
	int	i;
	int first;

	first = 1;
	i = 1;
	while (str[i])
	{
		char *env_value = get_env(str[i], env);
		if (!first)
            write(1, " ", 1);
		if (str[i] == env_value && env_value != NULL)
		{
			printf("%s", env_value);
		}
		else
			write(1, str[i], strlen(str[i]));
		first = 0;
		i++;
	}
}

void	print_string_with_option(char *str[])
{
	t_data *data = get_data();
	int	i;

	i = 2;
	while (str[i])
	{
		if (get_env(str[i], data->env) != NULL)
			printf("%s", get_env(str[i], data->env));
		else
			write(1, str[i], strlen(str[i]));
		if (str[i + 1] != NULL)
			write(1, " ", 1);
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
	t_data *data = get_data();
	if (strcmp(str[1], "-n") == 0 && str != NULL)
	{
		print_string_with_option(str);
	}
	else if (str != NULL)
	{
		print_string(str, data->env);
		printf("\n");
	}
	return (0);
}