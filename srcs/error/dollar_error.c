/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:54:55 by ylouvel           #+#    #+#             */
/*   Updated: 2024/10/22 13:14:19 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*get_before_dollar(char *str)
{
    t_data *data = get_data();
	int		i;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (str[i] != '$')
		return NULL;
    if(i != 0)
	    data->before = (char *)malloc(sizeof(char) * (i + 1));
	if (!data->before)
		return NULL;
	strncpy(data->before, str, i);
	data->before[i] = '\0';
    return NULL;
}

//! Si la variable est un path il faut retourner le msg d'erreur pour un dossier
int dollar_error(void)
{
	t_data *data = get_data();
    char *var_name;
    char *env_value;
	int i;
	i = 0;
    get_before_dollar(data->str[0]);
	if (data->str[0][0] == '$' && data->str[0][1] == '\0')
    {
		printf("minshell : $: Command not found\n");
        return 1;
    }
    while (data->str[0][i])
    {
        if (data->str[0][i] == '$' && data->str[0][i + 1] != '\0')
        {
            var_name = strdup(data->str[0] + i + 1);
            env_value = get_env(var_name, data->env);
            //! Si la variable est un path il faut retourner le msg d'erreur pour un dossier
            if (env_value != NULL)
            {
                printf("minishell: %s: Command not found\n", env_value);
                free(var_name);
                return 1;
            }
            if (data->before != NULL)
            {
                printf("minishell: %s: Command not found\n", data->before);
                free(var_name);
                return 1;
            }
        }
        i++;
    }
    i--;
    if(data->str[0][i] == '$')
        printf("minshell : %s: Command not found\n", data->str[0]);
    else
        return 1;
    return 0;
}
