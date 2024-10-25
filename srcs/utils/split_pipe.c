/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 21:37:08 by ylouvel           #+#    #+#             */
/*   Updated: 2024/10/25 21:43:08 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	first_verif(char *str, int i)
{
	while (str[i] && (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'))
		i++;
	return i;
}

int	second_verif(char *str, int i)
{
	while (str[i] && (str[i] != ' ' && str[i] != '\n' && str[i] != '\t'
			&& str[i] != '|'))
		i++;
	return i;
}

void init_var()
{
	t_data *data = get_data();
	data->i = 0;
	data->j = 0;
	data->k = 0;
}

char **sortie(char **out, int i, int j, char *str, int k)
{
	out[k] = (char *)malloc(sizeof(char) * ((i - j) + 1));
	if (!out[k])
	{
		while (k > 0)
			free(out[--k]);
		free(out);
		return (NULL);
	}
	strncpy(out[k], &str[j], i - j);
	out[k][i - j] = '\0';
	k++;
	return out;
}

//! 26 Lignes
char	**ft_split_pipe(char *str)
{
	t_data *data = get_data();
	char	**out;

	out = (char **)malloc(sizeof(char *) * (word_count_pipe(str) + 1));
	if (!out)
		return (NULL);
	while (str[data->i])
	{
		data->i = first_verif(str, data->i);
		if (str[data->i] == '|')
		{
			out = for_pipe(out, data->k);
			data->k++;
			data->i++;
		}
		data->j = data->i;
		data->i = second_verif(str, data->i);
		if (data->i > data->j)
		{
			out = sortie(out, data->i, data->j, str, data->k);
			data->k++;
		}
	}
	out[data->k] = NULL;
	init_var();
	return (out);
}
