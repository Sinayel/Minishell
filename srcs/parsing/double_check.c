/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 14:26:40 by ylouvel           #+#    #+#             */
/*   Updated: 2024/12/15 14:32:24 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_empty_input(char *input)
{
	if (strcmp(input, "") == 0)
		return (1);
	return (0);
}

int	handle_directory_case(char *input, t_data *data)
{
	if (is_directory(input))
	{
		if (input[0] == '.' || input[0] == '/')
		{
			ft_putstr_fd(input, 2);
			ft_putstr_fd(": Is a directory\n", 2);
			data->error = 126;
			return (2);
		}
		data->error = 127;
		return (1);
	}
	return (0);
}

int	handle_access_check(char *input)
{
	int	result;

	result = check_access(input);
	if (result == 0 || result == 3)
		return (result);
	return (-1);
}

int	handle_path_check(t_path *path, char *input, t_data *data)
{
	char	*word;
	int		result;

	while (path)
	{
		word = ft_magouilles(path->name, "/", input);
		result = check_access(word);
		if (result == 0)
		{
			free(word);
			return (result);
		}
		if (is_directory(word))
		{
			ft_putstr_fd(word, 2);
			ft_putstr_fd(": Is a directory\n", 2);
			data->error = 126;
			free(word);
			return (2);
		}
		free(word);
		path = path->next;
	}
	return (1);
}

int	double_check(t_path *path, char *input)
{
	t_data	*data;
	int		result;

	data = get_data();
	result = handle_empty_input(input);
	if (result != 0)
		return (result);
	result = handle_directory_case(input, data);
	if (result != 0)
		return (result);
	result = handle_access_check(input);
	if (result >= 0)
		return (result);
	return (handle_path_check(path, input, data));
}
