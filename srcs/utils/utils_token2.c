/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:11:55 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/28 16:12:16 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	while_str(char *str, int i)
{
	while (str[i] != '\'' && str[i] != '\"')
		i++;
	return (i);
}

int	len_for_quoted_token(char *str, int i)
{
	int	len;

	len = 0;
	i = while_str(str, i);
	if (str[i] == '\"')
	{
		len = 0;
		i++;
		while (str[i] != '\"' && str[i] != '\0')
		{
			len++;
			i++;
		}
	}
	else if (str[i] == '\'')
	{
		len = 0;
		i++;
		while (str[i] != '\'' && str[i] != '\0')
		{
			len++;
			i++;
		}
	}
	return (len);
}
