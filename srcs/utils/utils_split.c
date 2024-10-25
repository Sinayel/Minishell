/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 21:38:04 by ylouvel           #+#    #+#             */
/*   Updated: 2024/10/25 21:47:58 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	word_count_pipe(char *str)
{
	int	i;
	int	wc;

	i = 0;
	wc = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == '|' || str[i] == ' ' || str[i] == '\n'
				|| str[i] == '\t'))
		{
			if (str[i] == '|')
				wc++;
			i++;
		}
		if (str && str[i] != '\0')
			wc++;
		while (str[i] && (str[i] != '|' && str[i] != ' ' && str[i] != '\n'
				&& str[i] != '\t'))
			i++;
	}
	printf("wc = %d\n", wc);
	return (wc);
}

char **for_pipe(char **out, int k)
{
	out[k] = (char *)malloc(sizeof(char) * 2);
	if (!out[k])
	{
		while (k > 0)
			free(out[--k]);
		free(out);
		return (NULL);
	}
	out[k][0] = '|';
	out[k][1] = '\0';
	return out;
}
