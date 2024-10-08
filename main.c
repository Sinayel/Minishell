/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:16:17 by ylouvel           #+#    #+#             */
/*   Updated: 2024/10/07 21:24:12 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

//! ◦ CD with only a relative or absolute path |  (JULIO)
//! ◦ PWD with no options                      |  (JULIO)
//! ◦ UNSET with no options                    |  (JULIO)
//! ◦ EXPORT with no options                   |  (YANNS)
//! ◦ ENV with no options or arguments         |  (YANNS)
//! ◦ EXIT                                     |  (YANNS)

int ft_free(char **str)
{
    int i;

    i = 0;
    while (str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
    return (0);
}

int	parsing(char *str[])
{
	int	i;

	i = 0;
	if (str[i])
	{
		if (ft_strcmp(str[0], "echo") == 0)
			echo(str);
		if (ft_strcmp(str[0], "cd") == 0)
			printf("cd\n");
		if (ft_strcmp(str[0], "pwd") == 0)
			printf("pwd\n");
		if (ft_strcmp(str[0], "unset") == 0)
			printf("unset\n");
		if (ft_strcmp(str[0], "env") == 0)
			printf("env\n");
		if (ft_strcmp(str[0], "exit") == 0)
			printf("exit\n");
	}
	return (0);
}

int	main(void)
{
	char	*input;
	char	**str = NULL;

	while (1)
	{
		input = readline("Minishell$ ");
		str = ft_split(input);
		if (word_count(input) > 1)
		{
			parsing(str);
		}
		else if (word_count(input) == 1)
			echo_for_one_caractere(str[0]);
		if (*input)
			add_history(input);
		ft_free(str);
		free(input);
		rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
	}
	rl_clear_history();
	return (0);
}
