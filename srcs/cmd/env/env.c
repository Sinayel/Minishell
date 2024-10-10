/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 20:39:47 by ylouvel           #+#    #+#             */
/*   Updated: 2024/10/10 15:34:43 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char *get_env(const char *var, char **env)
{
    int i = 0;
    size_t len = strlen(var);

    while (env[i])
    {
        if (strncmp(env[i], var, len) == 0 && env[i][len] == '=')
        {
            return env[i] + len + 1;
        }
        i++;
    }
    return NULL;
}

void print_env()
{
    t_data *data = get_data();
    int i = 0;
    if (data->env != NULL)
    {
        while (data->env[i] != NULL)
        {
            printf("%s\n", data->env[i]);
            i++;
        }
    }
}
