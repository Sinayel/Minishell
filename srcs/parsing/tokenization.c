/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:29:09 by ylouvel           #+#    #+#             */
/*   Updated: 2024/10/28 18:03:31 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_separator(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

t_token	*tokenization(char *str)
{
	t_token	*list;
	int		i;
	int		j;
	char	*token;

	list = NULL;
	i = 0;
	j = 0;
	while (str[i])
	{
		skip_spaces(&i, str);
		j = i;
		token = extract_token(str, &i, j);
		if (token)
			list = add_last(list, token);
		handle_separator(&str, &i, &list);
	}
	return (list);
}

void	skip_spaces(int *i, char *str)
{
	while (str[*i] == ' ')
		(*i)++;
}

char	*extract_token(char *str, int *i, int j)
{
	while (str[*i] && !is_separator(str[*i]) && str[*i] != ' ')
		(*i)++;
	if (*i != j)
		return (ft_substr(str, j, *i - j));
	return (NULL);
}

void	handle_separator(char **str, int *i, t_token **list)
{
	char	*tmp;

	if (is_separator((*str)[*i]))
	{
		tmp = NULL;
		if ((*str)[*i] == '<' || (*str)[*i] == '>')
		{
			if ((*str)[*i + 1] == (*str)[*i])
			{
				tmp = ft_substr(*str, *i, 2);
				*i += 2;
			}
			else
			{
				tmp = ft_substr(*str, *i, 1);
				(*i)++;
			}
		}
		else if ((*str)[*i] == '|')
		{
			tmp = ft_substr(*str, *i, 1);
			(*i)++;
		}
		if (tmp)
			*list = add_last(*list, tmp);
	}
}
