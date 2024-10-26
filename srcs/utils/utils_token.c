/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 21:38:04 by ylouvel           #+#    #+#             */
/*   Updated: 2024/10/26 19:36:49 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_operator(char *str, int i)
{
	if (str[0] == '|' || str[0] == '<' || str[0] == '>')
		return (0);
	else if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i
		+ 1] == '<'))
		return 2;
	return 1;
}

int	word_count_pipe(char *str)
{
	int	i;
	int	wc;

	i = 0;
	wc = 0;
	while (str[i])
	{
		printf("wc = %d\n", wc);
		while (str[i] && (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'))
			i++;
		if (str[i] == '\0')
			break ;
		else if (is_operator(str, i) == 0 || is_operator(str, i) == 2)
		{
			if(is_operator(str, i) == 2)
				i += 2;
			else
				i++;
			wc++;
		}
		else
		{
			while (str[i] && str[i] != ' ' && str[i] != '\n' && str[i] != '\t')
			{
				i++;
				wc++;
			}
		}
	}
	return (wc);
}

char	**for_pipe(char **out, int k, char str)
{
	out[k] = (char *)malloc(sizeof(char) * 2);
	if (!out[k])
	{
		while (k > 0)
			free(out[--k]);
		free(out);
		return (NULL);
	}
	out[k][0] = str;
	out[k][1] = '\0';
	return (out);
}
