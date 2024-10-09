/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:00:45 by judenis           #+#    #+#             */
/*   Updated: 2024/10/09 11:05:57 by judenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int ft_exit(void)
{
    t_data *data = get_data();
    if (data->input)
        free(data->input);
    if (data->str)
        ft_free(data->str);
    rl_clear_history();
    exit(0);
    return (0);
}
