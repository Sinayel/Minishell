/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:29:09 by ylouvel           #+#    #+#             */
/*   Updated: 2024/10/31 13:55:04 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*extract_token(const char *str, int *i, int start)
{
	t_quote_state	state;
	bool			has_quotes;
	int				initial_start;

	state = (t_quote_state){false, false, false, false, false, 0};
	has_quotes = (str[start] == '"' || str[start] == '\'');
	initial_start = start;
	if (has_quotes)
		(*i)++;
	while (str[*i] && !state.should_break)
		process_token_char(str, i, has_quotes, &state);
	if (*i > initial_start)
		return (ft_substr(str, initial_start, *i - initial_start));
	return (NULL);
}

char	*create_separator_token(const char *str, int *i)
{
	char	*token;

	if ((str[*i] == '<' || str[*i] == '>') && str[*i + 1] == str[*i])
	{
		token = ft_substr(str, *i, 2);
		(*i)++;
	}
	else
		token = ft_substr(str, *i, 1);
	(*i)++;
	return (token);
}

void	handle_separator(const char *str, int *i, t_token **list)
{
	char	*token;

	token = NULL;
	if (is_separator(str[*i]) && !is_quoted(str, *i))
	{
		token = create_separator_token(str, i);
		if (token)
			*list = add_last(*list, token);
	}
}

void	process_token(char *str, int *i, t_token **list)
{
	int		start;
	char	*token;

	start = *i;
	token = extract_token(str, i, start);
	if (token)
		*list = add_last(*list, token);
	handle_separator(str, i, list);
}

t_token	*tokenization(char *str)
{
	t_token	*list;
	int		i;

	if (has_unclosed_quotes(str))
	{
		ft_putstr_fd("minishell: syntax error (open quotes)\n", 2);
		return (NULL);
	}
	list = NULL;
	i = 0;
	while (str[i])
	{
		skip_spaces(str, &i);
		if (!str[i])
			break ;
		process_token(str, &i, &list);
	}
	if(list)
		list = id_token(list);
	return (list);
}
