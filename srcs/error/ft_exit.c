/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:12:34 by ylouvel           #+#    #+#             */
/*   Updated: 2024/12/15 14:18:42 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	almost_atoi(char *str, int *err)
{
	unsigned long long	ret;
	int					i;
	int					j;
	int					pn;

	i = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	pn = 1;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			pn = -1;
	j = i;
	ret = 0;
	while ('0' <= str[i] && str[i] <= '9')
		ret = ret * 10 + (str[i++] - 48);
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] || i - j > 20 || ((pn == -1 && (ret - 1) > LONG_MAX) || (pn == 1
				&& (ret > LONG_MAX))))
		*err = 1;
	return ((int)((ret * pn) % 256));
}

int	ft_exit(t_token *list, t_env *env, t_path *path, char **args)
{
	int		ret;
	int		err;
	t_data	*data;

	data = get_data();
	ret = 0;
	err = 0;
	if (!args)
	{
		free_all(list, env, path);
		free_tabtab(args);
		exit(data->error);
	}
	else if (args[0])
	{
		ret = almost_atoi(args[0], &err);
		if (err)
			exit(print_numeric(args, list, env, path));
	}
	else if (args[0] && args[1])
		return (print_too_many(data, args));
	free_all(list, env, path);
	free_tabtab(args);
	exit(ret);
	return (0);
}

char	*error_free(char *str)
{
	t_data	*data;

	data = get_data();
	data->error = 1;
	free(str);
	ft_putstr_fd("bash: exit: too many arguments\n", 2);
	return (NULL);
}

char	*value_exit(t_token *tmp, char *value_for_exit)
{
	int	v;
	int	i;
	int	j;

	i = 0;
	j = 0;
	v = 0;
	while (tmp && tmp->type > 5)
	{
		while (tmp->token[j])
			value_for_exit[i++] = tmp->token[j++];
		if (tmp->next && tmp->next->type == ARG)
			return (error_free(value_for_exit));
		j = 0;
		v++;
		if (tmp->next)
			value_for_exit[i++] = ' ';
		tmp = tmp->next;
	}
	value_for_exit[i] = '\0';
	return (value_for_exit);
}

int	feat_arg_exit(t_token *list, t_env *env, t_path *path)
{
	int		len;
	t_token	*tmp;
	char	*value_for_exit;
	char	**split_exit;

	len = len_for_cd(list);
	tmp = list->next;
	if (len == 0)
		return (ft_exit(list, env, path, NULL));
	value_for_exit = (char *)malloc(sizeof(char) * (len + len));
	value_for_exit = value_exit(tmp, value_for_exit);
	if (value_for_exit == NULL)
		return (0);
	split_exit = ft_split(value_for_exit, ' ');
	free(value_for_exit);
	ft_exit(list, env, path, split_exit);
	return (0);
}
