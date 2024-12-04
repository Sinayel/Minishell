/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:39:51 by ylouvel           #+#    #+#             */
/*   Updated: 2024/12/04 18:56:32 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool	verif_token(char c)
{
	return (((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == 95)
		&& c != 32);
}

int	len_for_tmp(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && str[i] != '$')
			i++;
		if (str[i] == '$')
		{
			i++;
			while (str[i] && str[i] != '$' && verif_token(str[i]))
			{
				i++;
				j++;
			}
		}
	}
	return (j);
}

void	code(char *str, t_dollar *var, t_env *env, char *tmp)
{
	if ((str[var->i] == '\"' && str[var->i + 1] == '\'')
		|| (str[var->i] == '\''))
		return_quote(str, var);
	else if (var->in_single_quotes)
		var->finale[var->y++] = str[var->i++];
	else if (str[var->i] == '$' && verif_token(str[var->i + 1]))
		env_return_value(str, var, env, tmp);
	else if (str[var->i])
		var->finale[var->y++] = str[var->i++];
}

char	*proccess_dollar_value(char *str, t_env *env)
{
	t_dollar	*var;
	char		*tmp;
	char		*result;

	var = (t_dollar *)malloc(sizeof(t_dollar));
	if (!var)
		return (NULL);
	init_dollar_var(var, env, str);
	tmp = (char *)malloc(sizeof(char) * (var->len_tmp + 1));
	if (tmp)
		ft_memset(tmp, '\0', var->len_tmp + 1);
	while (str[var->i])
		code(str, var, env, tmp);
	var->y = 0;
	while (var->finale[var->y] == ' ')
		var->y++;
	if (var->tmp_y == var->y)
		return (free_dollar(var, tmp));
	var->y = var->tmp_y;
	free(tmp);
	var->finale[var->y] = '\0';
	result = ft_strdup(var->finale);
	free(var->finale);
	free(var);
	return (result);
}
