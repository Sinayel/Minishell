/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:12:44 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/26 18:13:36 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	**malloc_dest(t_export *export, char **dest)
{
	int	i;

	i = 0;
	while (export->content[i])
		i++;
	dest = (char **)malloc(sizeof(char *) * (i + 1));
	return (dest);
}

char	**return_dest(char **dest, t_export *export, int j)
{
	dest[j] = NULL;
	free_tabtab(export->content);
	return (dest);
}

void	free_name_and_value(t_env *temp)
{
	free(temp->name);
	free(temp->value);
	free(temp);
}

void	free_tabtab_unset(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	init_var_i(int *i, int *j)
{
	*i = 0;
	*j = 0;
}
