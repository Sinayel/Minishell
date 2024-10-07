/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:27:40 by judenis           #+#    #+#             */
/*   Updated: 2024/10/07 20:28:49 by judenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int ft_sig_handler(int sig, int raf)
{
    (void)raf;
    if (sig == SIGINT)
        exit(0);
}
int ft_strcmp(char *str, char *to_find)
{
    int i = 0;
    while (str[i] && to_find[i] && str[i] == to_find[i])
        i++;
    return (str[i] - to_find[i]);
}

int	main(void)
{
	char	*input;
	char	**str;

	while (1)
	{
		input = readline("Minishell$ ");
		if (word_count(input) > 1)
		{
			str = ft_split(input);
			parsing(str);
		}
		if (*input)
		{
			add_history(input);
		}
		free(input);
	}
	return (0);
}
