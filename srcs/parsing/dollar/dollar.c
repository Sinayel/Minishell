/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:39:51 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/12 18:48:53 by ylouvel          ###   ########.fr       */
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
	return ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == 95);
}

// t_token *return_pid(t_token *list, int pid, t_data *data)
// {
// 	int i;
// 	i = 0;
// 	while(pid > 0)
// 	{
// 		list->token[i] = ft_strdup(ft_itoa(data->pid));
// 		i += 2;
// 		pid--;
// 	}
// 	return list;
// }

char	*dollar_value(t_env *env, char *token, t_data *data, t_token *list)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;
	char	*value;
	int		pid;
	(void)list;
	(void)data;
	i = 0;
	j = 0;
	len = ft_strlen_dollar(token);
	tmp = malloc(sizeof(char) * (len + 1));
	while (token[i] == '$')
	{
		if (token[i + 1] == '$')
		{
			i++;
			pid++;
		}
		i++;
	}
	// if(pid)
	// 	return_pid(list, pid, data);
	if (i % 2 != 0)
	{
		while (token[i] && verif_token(token[i]))
		{
			tmp[j] = token[i];
			i++;
			j++;
			if (token[i + 1] == '$')
				continue ;
		}
		tmp[j] = '\0';
		value = return_env_value(env, tmp);
		if (return_env_value(env, tmp))
			return (value);
	}
	free(tmp);
	return (NULL);
}

bool	check_dollar(t_env *env, t_token *list, t_data *data)
{
	t_token	*tmp;
	int		i;

	tmp = list;
	i = 0;
	while (tmp)
	{
		if (dollar_value(env, tmp->token, data, tmp))
		{
			while (tmp->token[i] != '$')
				i++;
			tmp->token = ft_strdup(dollar_value(env, tmp->token, data, tmp));
			i = 1;
		}
		if (tmp->type == CMD && i == 1)
		{
			printf("Erreur dollar !\n");
			return (false);
		}
		tmp = tmp->next;
	}
	return (false);
}
