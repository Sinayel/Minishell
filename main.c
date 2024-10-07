/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:16:17 by ylouvel           #+#    #+#             */
/*   Updated: 2024/10/07 20:01:09 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/include.h"

//! ◦ CD with only a relative or absolute path |  (JULIO)
//! ◦ PWD with no options                      |  (JULIO)
//! ◦ UNSET with no options                    |  (JULIO)
//! ◦ EXPORT with no options                   |  (YANNS)
//! ◦ ENV with no options or arguments         |  (YANNS)
//! ◦ EXIT                                     |  (YANNS)

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

int	verif_input(char *input)
{
	int	i;

	i = 0;
	// printf("%s \n", input);
	
	while (input[i])
	{
		if (input[i] == ' ')
			return (1);
		i++;
	}
	return (0);
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
		else if (verif_input(input) == 1)
			echo_for_one_caractere(input);
		if (*input)
		{
			add_history(input);
		}
		free(input);
	}
	return (0);
}
