/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 20:41:12 by ylouvel           #+#    #+#             */
/*   Updated: 2024/10/11 19:54:34 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	write_env_var(char **str, char **env)
{
	t_data	*data;

	data = get_data();
	data->var_end = *str + 1;
	while (*data->var_end && (isalnum(*data->var_end) || *data->var_end == '_'))
		data->var_end++;
	data->var_name = strndup(*str, data->var_end - *str);
	data->env_value = get_env(data->var_name, env);
	free(data->var_name);
	if (data->env_value)
		write(1, data->env_value, strlen(data->env_value));
	else
		write(1, "$", 1);
	*str = data->var_end;
}

void	print_with_vars(char *str, char **env)
{
	t_data	*data;

	data = get_data();
	data->dollar_pos = strchr(str, '$');
	while (data->dollar_pos)
	{
		write(1, str, data->dollar_pos - str);
		str = data->dollar_pos + 1;
		if (*str)
			write_env_var(&str, env);
		data->dollar_pos = strchr(str, '$');
	}
	write(1, str, strlen(str));
}

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
		if (data->current_str[0] == '"')
		{
			data->inside_quotes = !data->inside_quotes;
			if (data->current_str[strlen(data->current_str) - 1] == '"')
				data->current_str[strlen(data->current_str) - 1] = '\0';
			data->current_str++;
		}
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