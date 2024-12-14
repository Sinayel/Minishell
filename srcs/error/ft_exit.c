/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:12:34 by ylouvel           #+#    #+#             */
/*   Updated: 2024/12/14 15:26:26 by ylouvel          ###   ########.fr       */
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

int	ft_exit(t_token *list, t_env *env, t_path *path, char **args)
{
	int	ret;
	int	err;
	t_data *data;

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
		{
			print_error("exit: ");
			print_error(args[0]);
			print_error(": numeric argument required\n");
			free_all(list, env, path);
			free_tabtab(args);
			exit(2);
		}
	}
	else if (args[0] && args[1])
	{
		print_error("exit: too many arguments\n");
		free_tabtab(args);
		data->error = 1;
		return 1;
	}
	free_all(list, env, path);
	free_tabtab(args);
	exit(ret);
	return 0;
}

int error_free(char *str)
{
	t_data *data;
	data = get_data();
	data->error = 1;
	free(str);
	printf("bash: exit: too many arguments\n");
	return 0;
}

int feat_arg_exit(t_token *list, t_env *env, t_path *path)
{
	int		len;
	t_token	*tmp;
	char	*value_for_exit;
	char 	**split_exit;
	int		i;
	int		j;
	int		v;
	v = 0;

	len = len_for_cd(list);
	tmp = list->next;
	if (len == 0)
		return (ft_exit(list, env, path, NULL));
	value_for_exit = (char *)malloc(sizeof(char) * (len + len));
	init_var_i(&i, &j);
	while (tmp && tmp->type > 5)
	{
		while (tmp->token[j])
			value_for_exit[i++] = tmp->token[j++];
		if (tmp->next && tmp->next->type == ARG)
			return (error_free(value_for_exit));
		j = 0;
		v++;
		if(tmp->next)
			value_for_exit[i++] = ' ';
		tmp = tmp->next;
	}
	value_for_exit[i] = '\0';
	split_exit = ft_split(value_for_exit, ' ');
	free(value_for_exit);
	ft_exit(list, env, path, split_exit);
	return (0);
}
