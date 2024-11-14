/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:29:09 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/14 16:15:13 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	openquote(char *line)
{
	int		i;
	bool	squote_open;
	bool	dquote_open;

	i = 0;
	squote_open = false;
	dquote_open = false;
	while (line[i])
	{
		if (line[i] == 34 && !squote_open)
			dquote_open = !dquote_open;
		if (line[i] == 39 && !dquote_open)
			squote_open = !squote_open;
		i++;
	}
	if (squote_open || dquote_open)
		return (true);
	return (false);
}

static char	*extract_token(char *str, int *i)
{
	int		start;
	char	quote_type;

	start = *i;
	quote_type = '\0';
	while (str[*i] && (!ft_isspace(str[*i]) || quote_type != '\0')
		&& !is_separator(str[*i]))
	{
		if (is_quote(str[*i]))
		{
			if (quote_type == '\0')
				quote_type = str[*i];
			else if (str[*i] == quote_type)
				quote_type = '\0';
		}
		(*i)++;
	}
	return (ft_substr(str, start, *i - start));
}

static char	*extract_separator_token(char *str, int *i)
{
	int	start;

	start = *i;
	if ((str[*i] == '<' || str[*i] == '>') && str[*i + 1] == str[*i])
	{
		(*i) += 2;
		return (ft_substr(str, start, 2));
	}
	(*i)++;
	return (ft_substr(str, start, 1));
}

t_token	*proccess_token(t_token *list, char *str)
{
	int		i;
	char	*token;

	i = 0;
	while (str[i])
	{
		skip_spaces(str, &i);
		if (!str[i])
			break ;
		if (is_separator(str[i]))
			token = extract_separator_token(str, &i);
		else
			token = extract_token(str, &i);
		if (token)
			list = add_last(list, token);
	}
	list = id_token(list);
	return (list);
}

t_token	*tokenization(char *str)
{
	t_token	*list;
	int		i;
	t_data	*data;

	data = get_data();
	i = 0;
	list = NULL;
	while (str[i] == ' ')
		i++;
	if (str[i] && !openquote(str))
	{
		str = proccess_pid(str, data);
		list = proccess_token(list, str);
		if(ft_strcmp(str, str) != 0)
			free(str);
	}
	else if (openquote(str))
		printf("open quote\n");
	return (list);
}
