/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:27:40 by judenis           #+#    #+#             */
/*   Updated: 2024/10/29 18:08:47 by judenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_sig_handler(int sig)
{
    if (sig == SIGINT)
    {
        printf("\n");
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
}


t_data *get_data(void)
{
    static t_data data;
    return (&data);
}

void ft_init_data(t_data *data)
{
    data->word_count = 0;
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

void setup_signals(void)
{
    struct sigaction sms;

    sms.sa_handler = ft_sig_handler;
    sigemptyset(&sms.sa_mask);
    sms.sa_flags = 0;
    sigaction(SIGINT, &sms, NULL);
}

int	main()  //, char **env
{
    t_data *data = get_data();
    ft_init_data(data);
    setup_signals();
	while (1)
	{
		data->input = readline("\033[1;33mMinishell$ \033[0m");
        if (data->input == NULL)
            ft_exit();
        data->word_count = word_count(data->input);
		if (data->word_count >= 1)
        {
            data->str = ft_split(data->input);
            ft_process();
        }
		if (*data->input)
			add_history(data->input);
		free(data->input);
        data->input = NULL;
	}
    rl_clear_history();
	return (0);
}
