/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:56:41 by ylouvel           #+#    #+#             */
/*   Updated: 2024/10/29 19:57:03 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void update_quote_state(char c, bool *in_squote, bool *in_dquote)
{
	if (c == '"' && !*in_squote)
		*in_dquote = !*in_dquote;
	else if (c == '\'' && !*in_dquote)
		*in_squote = !*in_squote;
}

bool	is_quoted(const char *str, int pos)
{
	bool	in_squote;
	bool	in_dquote;
	int		i;

	in_squote = false;
	in_dquote = false;
	i = 0;
	while (i < pos)
		update_quote_state(str[i++], &in_squote, &in_dquote);
	return (in_squote || in_dquote);
}

bool	should_break_token(const char *str, int i, bool has_quotes,
		bool in_squote, bool in_dquote)
{
	return (!has_quotes && !in_squote && !in_dquote
		&& (is_separator(str[i]) || isspace(str[i])));
}

void	handle_quotes(const char *str, int *i, int quote_type,
		t_quote_state *state)
{
	if (str[*i] == quote_type)
	{
		(*i)++;
		state->should_break = true;
	}
	else
		handle_quoted_content(str, i, &state->in_squote, &state->in_dquote);
}
