/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:30:11 by ylouvel           #+#    #+#             */
/*   Updated: 2024/12/13 22:24:39 by judenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_pwd(char *arg)
{
	char	cwd[4096];

	getcwd(cwd, sizeof(cwd));
	if (arg == NULL || (arg[0] == '-' && arg[1] == '\0') || arg[0] != '-')
	{
		printf("%s\n", cwd);
		return (0);
	}
	if (arg[0] == '-' && arg[1] == '-')
	{
		printf("bash: pwd: --: invalid option\n");
		return (0);
	}
	if (arg[0] == '-' && arg[1] != '\0')
	{
		printf("bash: pwd: %s: invalid option\n", arg);
		return (0);
	}
	return (1);
}

int	ft_arg_pwd(t_token *list)
{
	t_token	*tmp;
	int		len;

	len = len_for_cd(list);
	tmp = list->next;
	if (len == 0)
		return (ft_pwd(NULL));
	if (len > 1)
	{
		printf("bash: pwd: too many arguments\n");
		return (1);
	}
	return (ft_pwd(tmp->token));
}
