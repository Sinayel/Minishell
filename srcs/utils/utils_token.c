/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 21:38:04 by ylouvel           #+#    #+#             */
/*   Updated: 2024/10/29 20:17:07 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	process_token_char(const char *str, int *i, bool has_quotes,
		t_quote_state *state)
{
	if (str[*i] == '"' || str[*i] == '\'')
		handle_quotes(str, i, state->quote_type, state);
	else if (should_break_token(str, *i, has_quotes, state->in_squote,
			state->in_dquote))
		state->should_break = true;
	else
		(*i)++;
}

bool	has_unclosed_quotes(const char *line)
{
	t_quote_state	state;

	state = (t_quote_state){false, false, false, false, false, 0};
	for (int i = 0; line[i]; i++)
	{
		if (line[i] == '"' && !state.squote_open)
			state.dquote_open = !state.dquote_open;
		else if (line[i] == '\'' && !state.dquote_open)
			state.squote_open = !state.squote_open;
	}
	return (state.squote_open || state.dquote_open);
}

void	handle_quoted_content(const char *str, int *i, bool *in_squote,
		bool *in_dquote)
{
	if (str[*i] == '"' && !*in_squote)
	{
		*in_dquote = !*in_dquote;
		(*i)++;
	}
	else if (str[*i] == '\'' && !*in_dquote)
	{
		*in_squote = !*in_squote;
		(*i)++;
	}
	else
		(*i)++;
}

bool	is_separator(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

void	skip_spaces(const char *str, int *i)
{
	while (str[*i] && isspace(str[*i]))
		(*i)++;
}
