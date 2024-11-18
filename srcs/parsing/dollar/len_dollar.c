/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_dollar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:47:31 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/18 18:47:58 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void init_var_len(t_dollar_len *var, char *str)
{
	var->in_single_quotes = false;
	var->len_tmp = len_for_tmp(str);
	var->x = 0;
	var->y = 0;
	var->i = 0;
	var->j = 0;
}

void return_quote_len(t_dollar_len *var)
{
	var->in_single_quotes = !var->in_single_quotes;
    var->i++;
	var->y++;
}

void increm(t_dollar_len *var)
{
	var->i++;
	var->y++;
}

void env_return_value_len(t_dollar_len *var, char *tmp, t_env *env, char *str)
{
	var->i++;
	var->j = 0;
	while(str[var->i] && str[var->i] != '$' && verif_token(str[var->i]))
		tmp[var->j++] = str[var->i++];
	var->return_value = return_env_value(env, tmp);
	if(var->return_value)
	{
		while(var->return_value[var->x])
		{
			var->y++;
			var->x++;
		}
		free(var->return_value);
	}
	else
		var->return_value = NULL;
	var->x = 0;
}

int len_for_dollar(char *str, t_env *env, t_dollar_len *var)
{
	init_var_len(var, str);
	char *tmp = (char *)ft_calloc(var->len_tmp + 1, sizeof(char));
	while(str[var->i])
	{
		if ((str[var->i] == '\"' && str[var->i + 1] == '\'') || (str[var->i] == '\''))
            return_quote_len(var);
        else if (var->in_single_quotes)
			increm(var);
		else if(str[var->i] == '$' && verif_token(str[var->i + 1]))
			env_return_value_len(var, tmp, env, str);
		else if(str[var->i])
			increm(var);
	}
	free(tmp);
	return var->y;
}
