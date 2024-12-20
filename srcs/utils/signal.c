/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 19:44:12 by ylouvel           #+#    #+#             */
/*   Updated: 2024/12/15 14:55:09 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	signal_handler(int signum)
{
	t_data	*data;

	data = get_data();
	if (signum == SIGINT)
	{
		if (data->pid == 4242)
		{
			data->error = 130;
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else
		{
			printf("\n");
			data->error = 130;
		}
	}
}

void	handle_sigsegv(int code)
{
	(void)code;
	write(2, "Segmentation fault\n", 19);
	exit(11);
}

void	handle_sigabrt(int code)
{
	(void)code;
	write(1, "abort\n", 6);
}

void	signals2(void)
{
	t_data	*data;

	data = get_data();
	data->error = 130;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	signals(void)
{
	t_data	*data;

	data = get_data();
	data->pid = 4242;
	signal(SIGINT, signal_handler);
	signal(SIGSEGV, &handle_sigsegv);
	signal(SIGQUIT, SIG_IGN);
}
