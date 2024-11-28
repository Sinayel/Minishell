/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 21:38:04 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/19 17:56:43 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_quote(char c)
{
	return (c == '\"' || c == '\'');
}

bool	is_separator(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

bool	is_redirection(char *c)
{
	if (ft_strcmp(c, ">") == 0 || ft_strcmp(c, "<") == 0 || ft_strcmp(c,
			">>") == 0 || ft_strcmp(c, "<<") == 0)
		return (true);
	return (false);
}

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

void	skip_spaces(char *str, int *i)
{
	while (str[*i] && ft_isspace(str[*i]))
		(*i)++;
}
