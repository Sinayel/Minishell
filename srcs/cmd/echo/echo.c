/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 20:41:12 by ylouvel           #+#    #+#             */
/*   Updated: 2024/10/14 19:56:50 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	print_string(char *str[])
{
	t_data	*data;
	int		i;

	data = get_data();
	i = 1;
	data->inside_quotes = 0;
	while (str[i])
	{
		data->current_str = str[i];
		if (data->current_str[i] == '"')
		{
			data->inside_quotes = !data->inside_quotes;
			if (data->current_str[strlen(data->current_str) - 1] == '"' || data->current_str[strlen(data->current_str) - 1] != '$')
				data->current_str[strlen(data->current_str) - 1] = '\0';
			data->current_str++;
		}
		printf("data->current_str = %s\n", data->current_str);
		print_with_vars(data->current_str, data->env);
		if (str[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	return (data->inside_quotes);
}

void	print_string_with_option(char *str[])
{
	t_data	*data;
	int		i;

	data = get_data();
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
	t_data	*data = get_data();
	if (strcmp(str[1], "-n") == 0 && str != NULL)
	{
		print_string_with_option(str);
	}
	else if (str != NULL)
	{
		printf("str[1] = %s\n", str[1]);
		print_string(str);
		printf("%lu", strlen(data->current_str));
		printf("\n");
	}
	return (0);
}
