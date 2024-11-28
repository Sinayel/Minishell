/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:39:51 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/28 15:56:25 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*pid_len(int len, char *pid, char *str)
{
	int		pid_len;
	int		x;
	int		final_len;
	char	*tmp;

	pid_len = ft_strlen(pid);
	final_len = len;
	x = 0;
	while (x < len - 1)
	{
		if (str[x] == '$' && str[x + 1] == '$')
			final_len += pid_len - 2;
		x++;
	}
	tmp = malloc(sizeof(char) * (final_len + 1));
	return (tmp);
}

char	*return_quoted_value(char *str, char *tmp, int *j, int *i)
{
	tmp[*j] = str[*i];
	(*i)++;
	(*j)++;
	while (str[*i] != '\'' && str[*i] != '\0')
	{
		tmp[*j] = str[*i];
		(*i)++;
		(*j)++;
	}
	if (str[*i] == '\'')
	{
		tmp[*j] = str[*i];
		(*i)++;
		(*j)++;
	}
	return (tmp);
}

char	*get_pid(int len, char *str, char *pid)
{
	int		i;
	int		j;
	int		k;
	char	*tmp;

	tmp = pid_len(len, pid, str);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (str[i] == '\'')
			tmp = return_quoted_value(str, tmp, &j, &i);
		if (str[i] == '$' && str[i + 1] == '$')
		{
			k = 0;
			while (pid[k])
				tmp[j++] = pid[k++];
			i += 2;
		}
		else if (str[i])
			tmp[j++] = str[i++];
	}
	tmp[j] = '\0';
	return (tmp);
}

char	*proccess_pid(char *str)
{
	t_data	*data;
	int		len;
	char	*pid;
	char	*tmp;

	data = get_data();
	len = ft_strlen(str);
	pid = ft_itoa(data->pid);
	tmp = get_pid(len, str, pid);
	free(pid);
	return (tmp);
}
