/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 20:41:12 by ylouvel           #+#    #+#             */
/*   Updated: 2024/10/22 20:17:55 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// int	print_string(char *str[])
// {
// 	t_data	*data;
// 	int		i;

// 	data = get_data();
// 	i = 1;
// 	data->inside_quotes = 0;
// 	while (str[i])
// 	{
// 		data->current_str = str[i];
// 		printf("current = %s\n", data->current_str);
// 		if (data->current_str[i] == '"')
// 		{
// 			data->inside_quotes = !data->inside_quotes;
// 			printf("inside_quotes = %d\n", data->inside_quotes);
// 			if (data->current_str[strlen(data->current_str) - 1] == '"' || data->current_str[strlen(data->current_str) - 1] != '$')
// 				data->current_str[strlen(data->current_str) - 1] = '\0';
// 			data->current_str++;
// 		}
// 		print_with_vars(data->current_str, data->env);
// 		if (str[i + 1] != NULL)
// 			write(1, " ", 1);
// 		i++;
// 	}
// 	return (data->inside_quotes);
// }

int	print_string(char *str[])
{
	t_data	*data;
	int		i;
	int		j;
	int		n;

	data = get_data();
	i = 1;
	j = 0;
	n = 0;
	while (str[i])
	{
		j = 0;
		n = 0;
		if (strchr(str[i], '"'))
		{
			while(str[i][j])
			{
				if (str[i][j] == '"')
				{
					j++;
				}
				data->current_str[n] = str[i][j];
				n++;
				j++;
			}
		}
		// printf("current = %s\n", data->current_str);
		// print_with_vars(data->current_str, data->env);
		if (str[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	return (0);
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
	if (str[1] == NULL)
	{
		printf("\n");
		return (0);
	}
	if (strcmp(str[1], "-n") == 0 && str != NULL)
	{
		print_string_with_option(str);
		return 0;
	}
	else if (str != NULL)
	{
		print_string(str);
		printf("\n");
		return 0;
	}
	return (0);
}
