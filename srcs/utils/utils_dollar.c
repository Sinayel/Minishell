/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:19:15 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/22 11:35:18 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*proccess_dollar_1_on_2(t_dollar *var, char *tmp)
{
	int	tmp_y;

	tmp_y = var->y;
	var->y = 0;
	while (var->finale[var->y] == ' ')
		var->y++;
	if (tmp_y == var->y)
	{
		free_dollar(var, tmp);
		return (NULL);
	}
	var->y = tmp_y;
	return (var->finale);
}

void	init_dollar_var(t_dollar *var, t_env *env, char *str)
{
	t_dollar_len	*var_2;

	var_2 = (t_dollar_len *)malloc(sizeof(t_dollar_len));
	var->i = 0;
	var->y = 0;
	var->x = 0;
	var->j = 0;
	var->in_single_quotes = false;
	var->len_finale = len_for_dollar(str, env, var_2) + 1;
	var->tmp_y = var->len_finale - 1;
	var->len_tmp = len_for_tmp(str);
	var->finale = (char *)malloc(sizeof(char) * (var->len_finale));
	free(var_2);
	if (!var->finale)
	{
		perror("malloc failed");
		free(var);
		exit(EXIT_FAILURE);
	}
	memset(var->finale, '\0', var->len_finale);
}

void	env_return_value(char *str, t_dollar *var, t_env *env, char *tmp)
{
	var->i++;
	var->j = 0;
	while (str[var->i] && verif_token(str[var->i]))
		tmp[var->j++] = str[var->i++];
	tmp[var->j] = '\0';
	var->return_value = return_env_value(env, tmp);
	if (var->return_value)
	{
		var->x = 0;
		while (var->return_value[var->x])
		{
			var->finale[var->y] = var->return_value[var->x];
			var->y++;
			var->x++;
		}
	}
	else
		var->return_value = NULL;
}

void	return_quote(char *str, t_dollar *var)
{
	var->in_single_quotes = !var->in_single_quotes;
	var->finale[var->y++] = str[var->i++];
}

char	*free_dollar(t_dollar *var, char *tmp)
{
	free(var->return_value);
	free(var->finale);
	free(var);
	free(tmp);
	return (NULL);
}
