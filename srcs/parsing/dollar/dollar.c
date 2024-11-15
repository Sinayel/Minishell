/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:39:51 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/15 13:23:18 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_strlen_dollar(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] == '$')
		i++;
	while (str[i])
	{
		i++;
		j++;
	}
	return (j);
}

bool	verif_token(char c)
{
	return (((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == 95) && c != 32);
}

char	*dollar_value(t_env *env, char *token)
{
	int		i = 0, j;
	int		len;
	char	*tmp;
	char	*value;

	i = 0, j = 0;
	len = ft_strlen_dollar(token);
	tmp = (char *)malloc(sizeof(char) * (len + 1));
	value = NULL;
	while (token[i] && verif_token(token[i]))
		tmp[j++] = token[i++];
	tmp[j] = '\0';
	value = return_env_value(env, tmp);
	printf("value = %s\n", value);
	free(tmp);
	return (value);
}

bool if_is_quoted(char *str, int *j, int *i)
{
	if (str[*i] == '\'')
		return true;
	(*i)++;
	(*j)++;
	bool is_quote = false;

	while (str[*i] != '\'' && str[*i] != '\0')
	{
		(*i)++;
		(*j)++;
	}

	if (str[*i] == '\'')
	{
		(*i)++;
		(*j)++;
	}
	return is_quote;
}

int len_for_tmp(char *str)
{
	int i = 0;
	int j = 0;
	while(str[i])
	{
		while(str[i] && str[i] != '$')
			i++;
		if(str[i] == '$')
		{
			i++;
			while(str[i] && str[i] != '$' && verif_token(str[i]))
			{
				i++;
				j++;
			}
		}
	}
	return j;
}

int len_for_dollar(char *str, t_env *env)
{
	int i;
	int j;
	int y;
	int x;
	int len_tmp = len_for_tmp(str);
	char *tmp = (char *)malloc(sizeof(char) * len_tmp + 1);
	char *return_value;
	x = 0;
	y = 0;
	i = 0;
	j = 0;
	while(str[i])
	{
		while(str[i] && str[i] != '$')
		{
			y++;
			i++;
		}
		if(str[i] == '$')
		{
			i++;
			j = 0;
			while(str[i] && str[i] != '$' && verif_token(str[i]))
			{
				tmp[j] = str[i];
				i++;
				j++;
			}
			return_value = return_env_value(env, tmp);
			if(return_value)
			{
				while(return_value[x])
				{
					y++;
					x++;
				}
			}
			x = 0;
		}
	}
	free(tmp);
	// free(return_value);
	return y;
}

char *proccess_dollar_value(char *str, t_env *env)
{
	int i;
	int j;
	int y;
	int x;
	int len_tmp;
	int len_finale;
	char *tmp;
	char *finale;
	char *return_value;

	len_tmp = len_for_tmp(str);
	len_finale = len_for_dollar(str, env);
	tmp = (char *)malloc(sizeof(char) * (len_tmp + 1));
	if(tmp)
		memset(tmp, '\0', len_tmp + 1);
	finale = (char *)malloc(sizeof(char) * (len_finale + 1));
	i = 0;
	j = 0;
	y = 0;
	x = 0;
	while(str[i])
	{
		while(str[i] && str[i] != '$' || if_is_quoted(str, &y, &i))
		{
			finale[y] = str[i];
			y++;
			i++;
		}
		if(str[i] == '$' && str[i+1])
		{
			i++;
			j = 0;
			while(str[i] && str[i] != '$' && verif_token(str[i]))
			{
				tmp[j] = str[i];
				i++;
				j++;
			}
			return_value = return_env_value(env, tmp);
			if(return_value)
			{
				while(return_value[x])
				{
					finale[y] = return_value[x];
					y++;
					x++;
				}
			}
			x = 0;
		}
		if(str[i] == '$')
		{
			finale[y] = str[i];
			y++;
			i++;
		}
	}
	free(tmp);
	finale[y] = '\0';
	printf("finale = %s\n", finale);
	return str;
}
