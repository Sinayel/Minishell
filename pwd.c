/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:27:40 by judenis           #+#    #+#             */
/*   Updated: 2024/10/08 19:41:10 by judenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void ft_sig_handler(int sig)
{
    if (sig == SIGINT)
    {
        rl_replace_line("\n", 0);
        rl_on_new_line();
        rl_redisplay();
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

t_data *get_data(void)
{
    static t_data data;
    return (&data);
}

void ft_init_data(t_data *data)
{
    data->input = NULL;
    data->str = NULL;
}

int ft_pwd(void)
{
    char *pwd;

    pwd = getcwd(NULL, 0);
    printf("%s\n", pwd);
    free(pwd);
    return (0);
}

int ft_process(void)
{
    t_data *data = get_data();
    parsing();
    ft_free(data->str);
    return (0);
}

int	main()  //, char **env
{
    t_data *data = get_data();
    ft_init_data(data);
	struct sigaction	sms;

	sms.sa_handler = ft_sig_handler;	//* Definie ft_receiver comme gestionnaire de signaux (ce qui recois)
    sigemptyset(&sms.sa_mask);
	sms.sa_flags = 0;	
	sigaction(SIGINT, &sms, NULL);
	while (1)
	{
		data->input = readline("Minishell$ ");
		if (word_count(data->input) >= 1)
        {
            data->str = ft_split(data->input);
            ft_process();
        }
		if (*data->input)
        {
			add_history(data->input);
        }
		free(data->input);
	}
    rl_clear_history();
	return (0);
}
    