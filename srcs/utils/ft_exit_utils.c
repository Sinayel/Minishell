/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:21:47 by ylouvel           #+#    #+#             */
/*   Updated: 2024/12/12 20:26:21 by ylouvel          ###   ########.fr       */
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
	if (str[i] || i - j > 20 || ((pn == -1 && (ret - 1) > LONG_MAX) || \
		(pn == 1 && (ret > LONG_MAX))))
		*err = 1;
	return ((int)((ret * pn) % 256));
}

bool	print_error(char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
	return (true);
}

int	ft_exit(t_data *data, t_token *list, t_env *env, t_path *path)
{
	int	ret;
	int	err;
	t_token *tmp;

	tmp = list;
	ret = 0;
	err = 0;
	if (tmp->next && tmp->next->next)
	{
		print_error("exit: too many arguments\n");
		data->error = 1;
		return 1;
	}
	else if (tmp->next)
	{
		ret = almost_atoi(tmp->next->token, &err);
		if (err)
		{
			print_error("exit: ");
			print_error(tmp->next->token);
			print_error(": numeric argument required\n");
			free_all(list, env, path);
			exit(2);
		}
	}
	else if (!tmp->next)
	{
		free_all(list, env, path);
		exit(data->error);
	}
	free_all(list, env, path);
	exit(ret);
	return 0;
}

int feat_arg_exit(t_data *data, t_token *list, t_env *env, t_path *path)
{
	int		len;
	t_token	*tmp;
	char	*value_for_exit;
	int		i;
	int		j;

	len = len_for_cd(list);
	tmp = list->next;
	if (len == 0)
		return (ft_exit(data, list, env, path));
	value_for_exit = (char *)malloc(sizeof(char) * (len + 1));
	init_var_i(&i, &j);
	while (tmp && tmp->type > 5)
	{
		while (tmp->token[j])
			value_for_exit[i++] = tmp->token[j++];
		if (tmp->next && tmp->next->type == ARG)
			return (printf("bash: cd: too many arguments\n"));
		j = 0;
		tmp = tmp->next;
	}
	value_for_exit[i] = '\0';
	ft_exit(data, list, env, path);
	free(value_for_exit);
	return (0);
}