/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:02:02 by ylouvel           #+#    #+#             */
/*   Updated: 2024/10/10 19:48:45 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *short_cut(char *str)
{
    char *source;
    int i;
    int j;

    source = malloc(sizeof(char) * 100);
    i = 0;
    j = 0;
    if (str != NULL)
    {
        while (str[i])
        {
            if (str[i] == '$')
                i++;
            source[j] = str[i];
            i++;
            j++;
        }
        source[j] = '\0';
        return (source);
    }
    return (NULL);
}

void check_arg()
{
    t_data *data = get_data();
    char *source = malloc(sizeof(char) * 100);
    if (data->str[0][0] == '$')
    {
        source = short_cut(data->input);
        if (get_env(source, data->env) != NULL)
            printf("minishell: %s: command not found...\n", get_env(source, data->env));
    }
}