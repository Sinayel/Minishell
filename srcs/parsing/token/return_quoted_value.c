/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_quoted_value.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:11:08 by ylouvel           #+#    #+#             */
/*   Updated: 2024/12/03 14:47:41 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	skip_and_initialize_tmp(char **tmp, char *str, int *i, int len)
{
	*tmp = (char *)malloc(sizeof(char) * (len + 1));
	ft_memset(*tmp, '\0', len + 1);
	if (str[*i] == '\'' || str[*i] == '\"')
		(*i)++;
}

void	extract_quoted_content(char *tmp, char *str, int *i, char quote)
{
	int	len;

	len = 0;
	while (str[*i] != quote && str[*i] != '\0')
	{
		tmp[len] = str[*i];
		len++;
		(*i)++;
	}
	while (str[*i] == quote)
		(*i)++;
	tmp[len] = '\0';
}

char	*return_quoted_value_for_token(char *str, int *i)
{
	char	*tmp;
	int		len;

	len = len_for_quoted_token(str, *i);
	skip_and_initialize_tmp(&tmp, str, i, len);
	if (str[*i - 1] == '\"')
		extract_quoted_content(tmp, str, i, '\"');
	else if (str[*i - 1] == '\'')
		extract_quoted_content(tmp, str, i, '\'');
	return (tmp);
}
