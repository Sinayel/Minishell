/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:00:45 by judenis           #+#    #+#             */
/*   Updated: 2024/10/09 12:00:01 by judenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_free(char **str)
{
    int i;
    
    i = 0;
    while (i < word_count(str[0]))
    {
        free(str[i]);
        str[i] = NULL;
        i++;
    }
    if (str != NULL)
    {
        free(str);
        str = NULL;
    }
    return (0);
}

int ft_exit(void)
{
    t_data *data = get_data();
    if (data->input != NULL)
        free(data->input);
    if (data->str[0] && data->str)
        ft_free(data->str);
    rl_clear_history();
    exit(127);
    return (0);
}
