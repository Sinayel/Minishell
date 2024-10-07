/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:27:40 by judenis           #+#    #+#             */
/*   Updated: 2024/10/07 21:30:44 by judenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

volatile sig_atomic_t g_sigint_received = 0;

void ft_sig_handler(int sig)
{
    if (sig == SIGINT)
    {
        g_sigint_received = 1;
        rl_on_new_line();       // Déplace le curseur à une nouvelle ligne
        rl_replace_line("", 0); // Efface la ligne courante
        rl_redisplay();         // Redisplay le prompt
    }
}

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

int	main(void)
{
	char	*input;
	char	**str;

	while (1)
	{
        signal(SIGINT, ft_sig_handler);
		input = readline("Minishell$ ");
		if (word_count(input) >= 1)
		{
			str = ft_split(input);
			parsing(str);
            ft_free(str);
		}
        if (g_sigint_received)
        {
            g_sigint_received = 0;
            free(input);
            continue;
        }
		if (*input)
			add_history(input);
		free(input);
	}
	return (0);
}
