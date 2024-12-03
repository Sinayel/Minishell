/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:29:09 by ylouvel           #+#    #+#             */
/*   Updated: 2024/12/03 14:10:51 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
		if (str[i] == '\"' || str[i] == '\'')
			token = return_quoted_value_for_token(str, &i);
		else
		{
			if (is_separator(str[i]))
				token = extract_separator_token(str, &i);
			else
				token = extract_token(str, &i);
		}
		if (token)
			list = add_last(list, token);
	}
	list = id_token(list);
	return (list);
}

char	*verif_quote(char *str, int *i)
{
	while (str[*i] == ' ')
		(*i)++;
	if (openquote(str))
	{
		printf("open quote\n");
		return (NULL);
	}
	return (str);
}

char	*handle_dollar_and_errors(char *str, t_env *env)
{
	char	*tmp;

	tmp = proccess_error(str);
	if (tmp != str)
		str = tmp;
	tmp = proccess_dollar_value(str, env);
	if (tmp != str)
	{
		free(str);
		str = tmp;
	}
	return (str);
}

t_token	*finalize_tokens(t_token *list, char *str)
{
	if (str)
	{
		list = proccess_token(list, str);
		free(str);
	}
	return (list);
}

t_token	*tokenization(char *str, t_env *env)
{
	t_token	*list;
	int		i;

	list = NULL;
	i = 0;
	str = verif_quote(str, &i);
	if (str)
	{
		str = handle_dollar_and_errors(str, env);
		list = finalize_tokens(list, str);
	}
	return (list);
}
