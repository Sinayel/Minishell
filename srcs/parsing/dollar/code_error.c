/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:45:28 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/19 14:04:24 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*code_len(int len, char *pid, char *str)
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
		if (str[x] == '$' && str[x + 1] == '?')
			final_len += pid_len - 2;
		x++;
	}
	tmp = malloc(sizeof(char) * (final_len + 1));
	return (tmp);
}

char *return_quoted_value_error(char *str, char *tmp, int *j, int *i)
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

	return tmp;
}

char	*get_code(int len, char *str, char *code)
{
	int		i;
	int		j;
	int		k;
	char	*tmp;

	tmp = code_len(len, code, str);
	i = 0;
	j = 0;
	while (i < len)
	{
		if(str[i] == '\'')
			tmp = return_quoted_value_error(str, tmp, &j, &i);
		if (str[i] == '$' && str[i + 1] == '?')
		{
			k = 0;
			while (code[k])
				tmp[j++] = code[k++];
			i += 2;
		}
		else if(str[i])
			tmp[j++] = str[i++];
	}
	tmp[j] = '\0';
	return (tmp);
}

char	*proccess_error(char *str, t_data *data)
{
	int		len;
	char	*code;
	char	*tmp;

	len = ft_strlen(str);
	code = ft_itoa(data->error);
	tmp = get_code(len, str, code);
	free(code);
	return (tmp);
}
