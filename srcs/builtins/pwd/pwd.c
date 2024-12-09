/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:30:11 by ylouvel           #+#    #+#             */
/*   Updated: 2024/12/03 21:30:06 by ylouvel          ###   ########.fr       */
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
