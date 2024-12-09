/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:21:59 by ylouvel           #+#    #+#             */
/*   Updated: 2024/12/04 18:35:02 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*extract_separator_token(char *str, int *i)
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

char	*extract_token(char *str, int *i)
{
	int		j;
	char	quote_type;
	char	*tmp;

	tmp = (char *)malloc(sizeof(char) * strlen(str) + 1);
	j = 0;
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
		else
			tmp[j++] = str[*i];
		(*i)++;
	}
	tmp[j] = '\0';
	return (tmp);
}

// 5 Fonction pour verifier si c'est une cmd ou un argument
void	cmd_token(t_token *list)
{
	t_token	*tmp;
	t_token	*last;

	tmp = list;
	tmp->first = 1;
	if (tmp->type > PIPE)
		tmp->type = CMD;
	last = tmp;
	tmp = tmp->next;
	while (tmp != NULL)
	{
		if (last->type == PIPE && tmp->type == ARG)
			tmp->type = CMD;
		else if (tmp->type != PIPE && tmp->type >= PIPE)
			tmp->type = ARG;
		last = tmp;
		tmp = tmp->next;
	}
}

t_token	*id_token(t_token *list)
{
	t_token	*tmp;

	tmp = list;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->token, "|") == 0)
			tmp->type = PIPE;
		if (ft_strcmp(tmp->token, ">>") == 0)
			tmp->type = APPEND;
		if (ft_strcmp(tmp->token, "<<") == 0)
			tmp->type = HEREDOC;
		if (ft_strcmp(tmp->token, ">") == 0)
			tmp->type = TRUNC;
		if (ft_strcmp(tmp->token, "<") == 0)
			tmp->type = INPUT;
		if (tmp->type == 0 || ft_strcmp(tmp->token, " ") == 0)
			tmp->type = ARG;
		tmp = tmp->next;
	}
	cmd_token(list);
	return (list);
}
